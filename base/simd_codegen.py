from dataclasses import dataclass
from typing import List, Dict, Optional, Any, Callable

def emit_shift_scalar_expr(op: str, type_: str) -> str:
    match op:
        case "shl":
            return "a[i] << shift_by"
        case "shr":
            return "a[i] >> shift_by"
        case "shr_u":
            match type_:
                case "u8" | "u16" | "u32" | "u64":
                    return "a[i] >> shift_by"
                case _:
                    raise ValueError(f"unsupported shift op/type combo: {op} {type_}")
    raise ValueError(f"unsupported shift op: {op}")




def emit_stc_template_function_body_logical_binary(
    op: str,
    type_: str,
    simd_type: str,
    simd_store_func: str,
    simd_load_func: str,
    simd_op_func: str,
    simd_lanes: str,
    simd_cast: str
) -> str:
    if type_ == "f32":
        scalar_expr_u32 = {
            "and": "ua.u & ub.u",
            "or": "ua.u | ub.u",
            "xor": "ua.u ^ ub.u",
            "andnot": "(~ua.u) & ub.u",
        }[op]
        scalar_tail = f"""
    while (rem) {{
        union {{ u32 u; f32 f; }} ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = {scalar_expr_u32};
        a[i] = ur.f;
        ++i;
        --rem;
    }}
"""
    else:
        scalar_expr = {
            "and": "a[i] & b[i]",
            "or": "a[i] | b[i]",
            "xor": "a[i] ^ b[i]",
            "andnot": "(~a[i]) & b[i]",
        }[op]
        scalar_tail = f"""
    while (rem) {{
        a[i] = {scalar_expr};
        ++i;
        --rem;
    }}
"""
    return f"""
static inline void stc_simd_{op}_{type_}({type_} * restrict a, const {type_} * restrict b, const u64 len)
{{
    const u64 width = {simd_lanes};
    u64 rem = len % width;
    u64 i = 0;

    for (; (i + width) <= len; i += width) {{
        {simd_type} va = {simd_load_func}((const {simd_cast}*)(a + i));
        {simd_type} vb = {simd_load_func}((const {simd_cast}*)(b + i));
        {simd_type} result = {simd_op_func}(va, vb);
        {simd_store_func}(({simd_cast}*)(a + i), result);
    }}

{scalar_tail.rstrip()}
}}
""".strip()


def emit_stc_template_function_body_logical_unary(
    op: str,
    type_: str,
    simd_type: str,
    simd_store_func: str,
    simd_load_func: str,
    simd_op_func: str,
    simd_lanes: str,
    simd_cast: str,
    scalar_symbol: str
) -> str:
    if type_ == "f32" and scalar_symbol == "~":
        scalar_tail = """
    while (rem) {
        union { u32 u; f32 f; } ua;
        ua.f = a[i];
        ua.u = ~ua.u;
        a[i] = ua.f;
        ++i;
        --rem;
    }
"""
    else:
        scalar_tail = f"""
    while (rem) {{
        a[i] = {scalar_symbol}a[i];
        ++i;
        --rem;
    }}
"""
    return f"""
static inline void stc_simd_{op}_{type_}({type_} * restrict a, const u64 len)
{{
    const u64 width = {simd_lanes};
    u64 rem = len % width;
    u64 i = 0;

    for (; (i + width) <= len; i += width) {{
        {simd_type} va = {simd_load_func}((const {simd_cast}*)(a + i));
        {simd_type} result = {simd_op_func}(va);
        {simd_store_func}(({simd_cast}*)(a + i), result);
    }}

{scalar_tail.rstrip()}
}}
""".strip()


def emit_stc_template_function_body_compare(
    op: str,
    type_: str,
    simd_type: str,
    simd_store_func: str,
    simd_load_func: str,
    simd_op_func: str,
    simd_lanes: str,
    simd_cast: str,
    scalar_cmp_expr: str
) -> str:
    return f"""
static inline void stc_simd_{op}_{type_}({type_} * restrict a, const {type_} * restrict b, const u64 len)
{{
    const u64 width = {simd_lanes};
    u64 rem = len % width;
    u64 i = 0;

    for (; (i + width) <= len; i += width) {{
        {simd_type} va = {simd_load_func}((const {simd_cast}*)(a + i));
        {simd_type} vb = {simd_load_func}((const {simd_cast}*)(b + i));
        {simd_type} result = {simd_op_func}(va, vb);
        {simd_store_func}(({simd_cast}*)(a + i), result);
    }}

    while (rem) {{
        a[i] = ({scalar_cmp_expr}) ? ({type_})~0 : ({type_})0;
        ++i;
        --rem;
    }}
}}
""".strip()


def emit_stc_template_function_body_shift(
    op: str,
    type_: str,
    simd_type: str,
    simd_store_func: str,
    simd_load_func: str,
    simd_op_func: str,
    simd_lanes: str,
    simd_cast: str,
    scalar_shift_expr: str
) -> str:
    return f"""
static inline void stc_simd_{op}_{type_}({type_} * restrict a, const u32 shift_by, const u64 len)
{{
    const u64 width = {simd_lanes};
    u64 rem = len % width;
    u64 i = 0;

    for (; (i + width) <= len; i += width) {{
        {simd_type} va = {simd_load_func}((const {simd_cast}*)(a + i));
        {simd_type} result = {simd_op_func}(va, shift_by);
        {simd_store_func}(({simd_cast}*)(a + i), result);
    }}

    while (rem) {{
        a[i] = {scalar_shift_expr};
        ++i;
        --rem;
    }}
}}
""".strip()


def emit_stc_template_function_body_splat(
    type_: str,
    simd_type: str,
    simd_store_func: str,
    simd_set_func: str,
    simd_lanes: str,
    simd_cast: str
) -> str:
    return f"""
static inline void stc_simd_splat_{type_}({type_} * restrict a, const {type_} value, const u64 len)
{{
    const u64 width = {simd_lanes};
    u64 rem = len % width;
    u64 i = 0;

    {simd_type} vv = {simd_set_func}(value);

    for (; (i + width) <= len; i += width) {{
        {simd_store_func}(({simd_cast}*)(a + i), vv);
    }}

    while (rem) {{
        a[i] = value;
        ++i;
        --rem;
    }}
}}
""".strip()


def emit_simd_cast(type_: str) -> str:
    cast_ty: str = simd_cast_mapping[type_];
    return cast_ty;

def lanes(backend, type_) -> int:
    return backend_bits[backend] // (type_sizes[type_] * 8);

def emit_stc_template_function_signature_arith(op: str, type_: str) -> str:
    return f"static inline void stc_simd_{op}_{type_}({type_} * restrict a, const {type_} * restrict b, const u64 len);";

def emit_stc_template_function_signature_logical_binary(op: str, type_: str) -> str:
    return f"static inline void stc_simd_{op}_{type_}({type_} * restrict a, const {type_} * restrict b, const u64 len);"

def emit_stc_template_function_signature_logical_unary(op: str, type_: str) -> str:
    return f"static inline void stc_simd_{op}_{type_}({type_} * restrict a, const u64 len);"

def emit_stc_template_function_signature_any_true(type_: str) -> str:
    return f"static inline bool stc_simd_any_true_{type_}(const {type_} * restrict a, const u64 len);"

def emit_stc_template_function_signature_bitmask(type_: str) -> str:
    return f"static inline u64 stc_simd_bitmask_{type_}(const {type_} * restrict a, const u64 len);"

def emit_stc_template_function_signature_all_true(type_: str) -> str:
    return f"static inline bool stc_simd_all_true_{type_}(const {type_} * restrict a, const u64 len);"

def emit_stc_template_function_signature_count_true(type_: str) -> str:
    return f"static inline u64 stc_simd_count_true_{type_}(const {type_} * restrict a, const u64 len);"

def emit_stc_template_function_signature_first_true(type_: str) -> str:
    return f"static inline u64 stc_simd_first_true_{type_}(const {type_} * restrict a, const u64 len);"

def emit_stc_template_function_signature_count_compare_scalar(op: str, type_: str) -> str:
    return f"static inline u64 stc_simd_count_{op}_scalar_{type_}(const {type_} * restrict a, const {type_} value, const u64 len);"

def emit_stc_template_function_signature_first_compare_scalar(op: str, type_: str) -> str:
    return f"static inline u64 stc_simd_first_{op}_scalar_{type_}(const {type_} * restrict a, const {type_} value, const u64 len);"

def emit_stc_template_function_signature_set_splat(type_: str) -> str:
    return f"static inline void stc_simd_splat_{type_}({type_} * restrict a, const {type_} value, const u64 len);"

def emit_stc_template_function_signature_shift(op: str, type_: str) -> str:
    return f"static inline void stc_simd_{op}_{type_}({type_} * restrict a, const u32 shift_by, const u64 len);"

def emit_stc_template_function_signature_compare(op: str, type_: str) -> str:
    return f"static inline void stc_simd_{op}_{type_}({type_} * restrict a, const {type_} * restrict b, const u64 len);"



def emit_stc_template_function_body_arith(
    op: str,
    type_: str,
    simd_type: str,
    simd_store_func: str,
    simd_load_func: str,
    simd_op_func: str,
    simd_op_symbol: str,
    simd_lanes: str,
    simd_cast: str
) -> str:
    return f"""
static inline void stc_simd_{op}_{type_}({type_} * restrict a, const {type_} * restrict b, const u64 len)
{{
    const u64 width = {simd_lanes};
    u64 rem = len % width;
    u64 i = 0;

    for (; (i + width) <= len; i += width) {{
        {simd_type} va = {simd_load_func}((const {simd_cast}*)(a + i));
        {simd_type} vb = {simd_load_func}((const {simd_cast}*)(b + i));
        {simd_type} result = {simd_op_func}(va, vb);
        {simd_store_func}(({simd_cast}*)(a + i), result);
    }}

    while (rem) {{
        a[i] {simd_op_symbol}= b[i];
        ++i;
        --rem;
    }}
}}
""".strip();

def emit_stc_template_function_body_minmax(
    op: str,
    type_: str,
    simd_type: str,
    simd_store_func: str,
    simd_load_func: str,
    simd_op_func: str,
    simd_lanes: str,
    simd_cast: str,
    scalar_expr: str,
) -> str:
    return f"""
static inline void stc_simd_{op}_{type_}({type_} * restrict a, const {type_} * restrict b, const u64 len)
{{
    const u64 width = {simd_lanes};
    u64 rem = len % width;
    u64 i = 0;

    for (; (i + width) <= len; i += width) {{
        {simd_type} va = {simd_load_func}((const {simd_cast}*)(a + i));
        {simd_type} vb = {simd_load_func}((const {simd_cast}*)(b + i));
        {simd_type} result = {simd_op_func}(va, vb);
        {simd_store_func}(({simd_cast}*)(a + i), result);
    }}

    while (rem) {{
        a[i] = {scalar_expr};
        ++i;
        --rem;
    }}
}}
""".strip()


ops_arith_symbol_mapping: Dict[str, str] = {
    "add": "+",
    "mul": "*",
    "div": "/",
    "sub": "-",
}

ops_bit_symbol_mapping: Dict[str, str] = {
    "and": "&",
    "or": "|",
    "not": "~",
    "xor": "^",
}

backend_emitteer: Dict[str, Dict[str, Any]] = {
    "WASM": {
    "Swizzle": {
        "swizzle": {
            "i8": "wasm_i8x16_swizzle",
        },
        "shuffle": {
            # lane-immediate style families also exist in wasm_simd128.h
        },
    },

    "Logical": {
        "and": "wasm_v128_and",
        "or":  "wasm_v128_or",
        "xor": "wasm_v128_xor",
        "not": "wasm_v128_not",
        "andnot": "wasm_v128_andnot",
        "bitselect": "wasm_v128_bitselect",
        "any_true": "wasm_v128_any_true",
    },

    "Bit Manipulation": {
        "bitmask": {
            "i8":  "wasm_i8x16_bitmask",
            "i16": "wasm_i16x8_bitmask",
            "i32": "wasm_i32x4_bitmask",
            "i64": "wasm_i64x2_bitmask",
        },
        "all_true": {
            "i8":  "wasm_i8x16_all_true",
            "i16": "wasm_i16x8_all_true",
            "i32": "wasm_i32x4_all_true",
            "i64": "wasm_i64x2_all_true",
        },
    },

    "Set": {
        "splat": {
            "i8":  "wasm_i8x16_splat",
            "i16": "wasm_i16x8_splat",
            "i32": "wasm_i32x4_splat",
            "i64": "wasm_i64x2_splat",
            "f32": "wasm_f32x4_splat",
            "f64": "wasm_f64x2_splat",
        },
        "make": {
            "i8":  "wasm_i8x16_make",
            "i16": "wasm_i16x8_make",
            "i32": "wasm_i32x4_make",
            "i64": "wasm_i64x2_make",
            "f32": "wasm_f32x4_make",
            "f64": "wasm_f64x2_make",
        },
    },

    "Shift": {
        "shl": {
            "i8":  "wasm_i8x16_shl",
            "i16": "wasm_i16x8_shl",
            "i32": "wasm_i32x4_shl",
            "i64": "wasm_i64x2_shl",
        },
        "shr": {
            "i8":  "wasm_i8x16_shr",
            "i16": "wasm_i16x8_shr",
            "i32": "wasm_i32x4_shr",
            "i64": "wasm_i64x2_shr",
        },
        "shr_u": {
            "u8":  "wasm_u8x16_shr",
            "u16": "wasm_u16x8_shr",
            "u32": "wasm_u32x4_shr",
            "u64": "wasm_u64x2_shr",
        },
    },

    "Compare": {
        "cmpeq": {
            "i8":  "wasm_i8x16_eq",
            "i16": "wasm_i16x8_eq",
            "i32": "wasm_i32x4_eq",
            "i64": "wasm_i64x2_eq",
            "f32": "wasm_f32x4_eq",
            "f64": "wasm_f64x2_eq",
        },
        "cmpne": {
            "i8":  "wasm_i8x16_ne",
            "i16": "wasm_i16x8_ne",
            "i32": "wasm_i32x4_ne",
            "i64": "wasm_i64x2_ne",
            "f32": "wasm_f32x4_ne",
            "f64": "wasm_f64x2_ne",
        },
        "cmplt": {
            "i8":  "wasm_i8x16_lt",
            "i16": "wasm_i16x8_lt",
            "i32": "wasm_i32x4_lt",
            "f32": "wasm_f32x4_lt",
            "f64": "wasm_f64x2_lt",
        },
        "cmpgt": {
            "i8":  "wasm_i8x16_gt",
            "i16": "wasm_i16x8_gt",
            "i32": "wasm_i32x4_gt",
            "f32": "wasm_f32x4_gt",
            "f64": "wasm_f64x2_gt",
        },
        "cmple": {
            "i8":  "wasm_i8x16_le",
            "i16": "wasm_i16x8_le",
            "i32": "wasm_i32x4_le",
            "f32": "wasm_f32x4_le",
            "f64": "wasm_f64x2_le",
        },
        "cmpge": {
            "i8":  "wasm_i8x16_ge",
            "i16": "wasm_i16x8_ge",
            "i32": "wasm_i32x4_ge",
            "f32": "wasm_f32x4_ge",
            "f64": "wasm_f64x2_ge",
        },
    },
        "Arithmetic": {
            "add": {
                "i64": "wasm_i64x2_add",
                "i32": "wasm_i32x4_add",
                "i16": "wasm_i16x8_add",
                "i8":  "wasm_i8x16_add",
                "f32": "wasm_f32x4_add",
            },
            "mul": {
                "i32": "wasm_i32x4_mul",
                "i16": "wasm_i16x8_mul",
                "f32": "wasm_f32x4_mul",
            },
            "sub": {
                "i64": "wasm_i64x2_sub",
                "i32": "wasm_i32x4_sub",
                "i16": "wasm_i16x8_sub",
                "i8":  "wasm_i8x16_sub",
                "f32": "wasm_f32x4_sub",
            },
            "div": {
                "f32": "wasm_f32x4_div",
            }
        },
        "MinMax": {
            "min": {
                "i32": "wasm_i32x4_min",
                "f32": "wasm_f32x4_min",
            },
            "max": {
                "i32": "wasm_i32x4_max",
                "f32": "wasm_f32x4_max",
            },
        },
        "Load": "wasm_v128_load",
        "Store": "wasm_v128_store",
    },
    "SSE42": {
    "Swizzle": {},
        "Logical": {
            "and": {
                "i8": "_mm_and_si128",
                "i16": "_mm_and_si128",
                "i32": "_mm_and_si128",
                "i64": "_mm_and_si128",
                "f32": "_mm_and_ps",
            },
            "or": {
                "i8": "_mm_or_si128",
                "i16": "_mm_or_si128",
                "i32": "_mm_or_si128",
                "i64": "_mm_or_si128",
                "f32": "_mm_or_ps",
            },
            "xor": {
                "i8": "_mm_xor_si128",
                "i16": "_mm_xor_si128",
                "i32": "_mm_xor_si128",
                "i64": "_mm_xor_si128",
                "f32": "_mm_xor_ps",
            },
            "andnot": {
                "i8": "_mm_andnot_si128",
                "i16": "_mm_andnot_si128",
                "i32": "_mm_andnot_si128",
                "i64": "_mm_andnot_si128",
                "f32": "_mm_andnot_ps",
            },
        },
        "Bit Manipulation": {
            "movemask": {
                "i8": "_mm_movemask_epi8",
                "f32": "_mm_movemask_ps",
            },
        },
        "Set": {
            "set1": {
                "i8": "_mm_set1_epi8",
                "i16": "_mm_set1_epi16",
                "i32": "_mm_set1_epi32",
                "i64": "_mm_set1_epi64x",
                "f32": "_mm_set1_ps",
            },
            "setzero": {
                "i8": "_mm_setzero_si128",
                "i16": "_mm_setzero_si128",
                "i32": "_mm_setzero_si128",
                "i64": "_mm_setzero_si128",
                "f32": "_mm_setzero_ps",
            },
        },
        "Shift": {
            "shl": {
                "i16": "_mm_slli_epi16",
                "i32": "_mm_slli_epi32",
                "i64": "_mm_slli_epi64",
            },
            "shr": {
                "i16": "_mm_srai_epi16",
                "i32": "_mm_srai_epi32",
            },
            "shr_u": {
                "u16": "_mm_srli_epi16",
                "u32": "_mm_srli_epi32",
                "u64": "_mm_srli_epi64",
            },
        },
        "Compare": {
            "cmp": {},
            "cmpeq": {
                "i8": "_mm_cmpeq_epi8",
                "i16": "_mm_cmpeq_epi16",
                "i32": "_mm_cmpeq_epi32",
                "i64": "_mm_cmpeq_epi64",
                "f32": "_mm_cmpeq_ps",
            },
            "cmpgt": {
                "i8": "_mm_cmpgt_epi8",
                "i16": "_mm_cmpgt_epi16",
                "i32": "_mm_cmpgt_epi32",
                "i64": "_mm_cmpgt_epi64",
                "f32": "_mm_cmpgt_ps",
            },
        },
        "Arithmetic": {
            "add": {
                "i64": "_mm_add_epi64",
                "i32": "_mm_add_epi32",
                "i16": "_mm_add_epi16",
                "i8":  "_mm_add_epi8",
                "f32": "_mm_add_ps",
            },
            "mul": {
                "i32": "_mm_mullo_epi32",
                "i16": "_mm_mullo_epi16",
                "f32": "_mm_mul_ps",
            },
            "sub": {
                "i64": "_mm_sub_epi64",
                "i32": "_mm_sub_epi32",
                "i16": "_mm_sub_epi16",
                "i8":  "_mm_sub_epi8",
                "f32": "_mm_sub_ps",
            },
            "div": {
                "f32": "_mm_div_ps",
            }
        },
        "MinMax": {
            "min": {
                "i32": "_mm_min_epi32",
                "f32": "_mm_min_ps",
            },
            "max": {
                "i32": "_mm_max_epi32",
                "f32": "_mm_max_ps",
            },
        },
        "Load": {
            "f32": "_mm_load_ps",
            "i8": "_mm_load_si128",
            "i16": "_mm_load_si128",
            "i32": "_mm_load_si128",
            "i64": "_mm_load_si128",
        },
        "Store": {
            "f32": "_mm_store_ps",
            "i8":  "_mm_store_si128",
            "i16": "_mm_store_si128",
            "i32": "_mm_store_si128",
            "i64": "_mm_store_si128",
        },
    },
    "AVX2": {
     "Swizzle": {},
        "Logical": {
            "and": {
                "i8": "_mm256_and_si256",
                "i16": "_mm256_and_si256",
                "i32": "_mm256_and_si256",
                "i64": "_mm256_and_si256",
                "f32": "_mm256_and_ps",
            },
            "or": {
                "i8": "_mm256_or_si256",
                "i16": "_mm256_or_si256",
                "i32": "_mm256_or_si256",
                "i64": "_mm256_or_si256",
                "f32": "_mm256_or_ps",
            },
            "xor": {
                "i8": "_mm256_xor_si256",
                "i16": "_mm256_xor_si256",
                "i32": "_mm256_xor_si256",
                "i64": "_mm256_xor_si256",
                "f32": "_mm256_xor_ps",
            },
            "andnot": {
                "i8": "_mm256_andnot_si256",
                "i16": "_mm256_andnot_si256",
                "i32": "_mm256_andnot_si256",
                "i64": "_mm256_andnot_si256",
                "f32": "_mm256_andnot_ps",
            },
        },
        "Bit Manipulation": {
            "movemask": {
                "i8": "_mm256_movemask_epi8",
                "f32": "_mm256_movemask_ps",
            },
        },
        "Set": {
            "set1": {
                "i8": "_mm256_set1_epi8",
                "i16": "_mm256_set1_epi16",
                "i32": "_mm256_set1_epi32",
                "i64": "_mm256_set1_epi64x",
                "f32": "_mm256_set1_ps",
            },
            "setzero": {
                "i8": "_mm256_setzero_si256",
                "i16": "_mm256_setzero_si256",
                "i32": "_mm256_setzero_si256",
                "i64": "_mm256_setzero_si256",
                "f32": "_mm256_setzero_ps",
            },
        },
        "Shift": {
            "shl": {
                "i16": "_mm256_slli_epi16",
                "i32": "_mm256_slli_epi32",
                "i64": "_mm256_slli_epi64",
            },
            "shr": {
                "i16": "_mm256_srai_epi16",
                "i32": "_mm256_srai_epi32",
            },
            "shr_u": {
                "u16": "_mm256_srli_epi16",
                "u32": "_mm256_srli_epi32",
                "u64": "_mm256_srli_epi64",
            },
        },
        "Compare": {
            "cmp": {},
            "cmpeq": {
                "i8": "_mm256_cmpeq_epi8",
                "i16": "_mm256_cmpeq_epi16",
                "i32": "_mm256_cmpeq_epi32",
                "i64": "_mm256_cmpeq_epi64",
                "f32": "_mm256_cmp_ps",
            },
            "cmpgt": {
                "i8": "_mm256_cmpgt_epi8",
                "i16": "_mm256_cmpgt_epi16",
                "i32": "_mm256_cmpgt_epi32",
                "i64": "_mm256_cmpgt_epi64",
                "f32": "_mm256_cmp_ps",
            },
        },
        "Arithmetic": {
            "add": {
                "i64": "_mm256_add_epi64",
                "i32": "_mm256_add_epi32",
                "i16": "_mm256_add_epi16",
                "i8":  "_mm256_add_epi8",
                "f32": "_mm256_add_ps",
            },
            "mul": {
                "i32": "_mm256_mullo_epi32",
                "i16": "_mm256_mullo_epi16",
                "f32": "_mm256_mul_ps",
            },
            "sub": {
                "i64": "_mm256_sub_epi64",
                "i32": "_mm256_sub_epi32",
                "i16": "_mm256_sub_epi16",
                "i8":  "_mm256_sub_epi8",
                "f32": "_mm256_sub_ps",
            },
            "div": {
                "f32": "_mm256_div_ps",
            }
        },
        "MinMax": {
            "min": {
                "i32": "_mm256_min_epi32",
                "f32": "_mm256_min_ps",
            },
            "max": {
                "i32": "_mm256_max_epi32",
                "f32": "_mm256_max_ps",
            },
        },
        "Load": {
            "f32": "_mm256_load_ps",
            "i8": "_mm256_load_si256",
            "i16": "_mm256_load_si256",
            "i32": "_mm256_load_si256",
            "i64": "_mm256_load_si256",
        },
        "Store": {
            "f32": "_mm256_store_ps",
            "i8":  "_mm256_store_si256",
            "i16": "_mm256_store_si256",
            "i32": "_mm256_store_si256",
            "i64": "_mm256_store_si256",
        },
    },
};

simd_type_order: List[str] = ["i8", "i16", "i32", "i64", "f32"]

type_to_simd: Dict[str, str] = {
    "i8": "simd_i8",
    "i16": "simd_i16",
    "i32": "simd_i32",
    "i64": "simd_i64",
    "f32": "simd_f32",
};

backend_guards: Dict[str, str] = {
    "WASM": "#if defined(__wasm_simd128__)",
    "SSE42": "#if defined(__SSE4_2__)",
    "AVX2": "#if defined(__AVX2__)",
};

backend_bits: Dict[str, int] = {
    "WASM": 128,
    "SSE42": 128,
    "AVX2": 256,
};

type_sizes: Dict[str, int] = {
    "i8": 1, "i16": 2, "i32": 4, "i64": 8,
    "f32": 4,
};

simd_cast_mapping: Dict[str, str] = {
    "f32" : "f32",
    "i8" : "simd_i8",
    "i16" : "simd_i16",
    "i32" : "simd_i32",
    "i64" : "simd_i64",
};

ops_arith_per_type: Dict[str, List[str]] = {
    "i8":  ["add", "sub"],
    "i16": ["add", "mul", "sub"],
    "i32": ["add", "mul", "sub"],
    "i64": ["add", "sub"],
    "f32": ["add", "mul", "sub", "div"],
};

ops_shift_per_type: Dict[str, List[str]] = {
    "i8":  ["shl", "shr"],
    "i16": ["shl", "shr"],
    "i32": ["shl", "shr"],
    "i64": ["shl", "shr"],
};

ops_logical_binary_per_type: Dict[str, List[str]] = {
    "i8":  ["and", "or", "xor", "andnot"],
    "i16": ["and", "or", "xor", "andnot"],
    "i32": ["and", "or", "xor", "andnot"],
    "i64": ["and", "or", "xor", "andnot"],
    "f32": ["and", "or", "xor", "andnot"],
};

ops_logical_unary_per_type: Dict[str, List[str]] = {
    "i8":  ["not"],
    "i16": ["not"],
    "i32": ["not"],
    "i64": ["not"],
    "f32": ["not"],
};

ops_compare_per_type: Dict[str, List[str]] = {
    "i8":  ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i16": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i32": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i64": ["cmpeq", "cmpne"],
    "f32": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
};

ops_set_splat_per_type: Dict[str, List[str]] = {
    "i8":  ["splat"],
    "i16": ["splat"],
    "i32": ["splat"],
    "i64": ["splat"],
    "f32": ["splat"],
};

ops_bitmask_per_type: Dict[str, List[str]] = {
    "i8":  ["bitmask"],
    "i16": ["bitmask"],
    "i32": ["bitmask"],
    "i64": ["bitmask"],
    "f32": ["bitmask"],
}

ops_all_true_per_type: Dict[str, List[str]] = {
    "i8":  ["all_true"],
    "i16": ["all_true"],
    "i32": ["all_true"],
    "i64": ["all_true"],
    "f32": ["all_true"],
}

ops_any_true_per_type: Dict[str, List[str]] = {
    "i8":  ["any_true"],
    "i16": ["any_true"],
    "i32": ["any_true"],
    "i64": ["any_true"],
    "f32": ["any_true"],
}

ops_minmax_per_type: Dict[str, List[str]] = {
    "i32": ["min", "max"],
    "f32": ["min", "max"],
}

cmp_scalar_expr: Dict[str, str] = {
    "cmpeq": "a[i] == b[i]",
    "cmpne": "a[i] != b[i]",
    "cmplt": "a[i] < b[i]",
    "cmpgt": "a[i] > b[i]",
    "cmple": "a[i] <= b[i]",
    "cmpge": "a[i] >= b[i]",
}

ops_count_true_per_type: Dict[str, List[str]] = {
    "i8": ["count_true"],
    "i16": ["count_true"],
    "i32": ["count_true"],
    "i64": ["count_true"],
    "f32": ["count_true"],
}

ops_first_true_per_type: Dict[str, List[str]] = {
    "i8": ["first_true"],
    "i16": ["first_true"],
    "i32": ["first_true"],
    "i64": ["first_true"],
    "f32": ["first_true"],
}

ops_count_compare_scalar_per_type: Dict[str, List[str]] = {
    "i8": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i16": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i32": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i64": ["cmpeq", "cmpne"],
    "f32": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
}

ops_first_compare_scalar_per_type: Dict[str, List[str]] = {
    "i8": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i16": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i32": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i64": ["cmpeq", "cmpne"],
    "f32": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
}


def emit_scalar_binary(op: str, type_: str, symbol: str) -> str:
    return f"""
static inline void stc_simd_{op}_{type_}({type_} * restrict a, const {type_} * restrict b, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        a[i] = a[i] {symbol} b[i];
    }}
}}
""".strip()


def emit_scalar_unary(op: str, type_: str, symbol: str) -> str:
    if type_ == "f32" and symbol == "~":
        return f"""
static inline void stc_simd_{op}_{type_}({type_} * restrict a, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        union {{ u32 u; f32 f; }} bits;
        bits.f = a[i];
        bits.u = ~bits.u;
        a[i] = bits.f;
    }}
}}
""".strip()
    return f"""
static inline void stc_simd_{op}_{type_}({type_} * restrict a, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        a[i] = {symbol}a[i];
    }}
}}
""".strip()


def emit_scalar_shift(op: str, type_: str) -> str:
    expr = emit_shift_scalar_expr(op, type_)
    return f"""
static inline void stc_simd_{op}_{type_}({type_} * restrict a, const u32 shift_by, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        a[i] = {expr};
    }}
}}
""".strip()


def emit_scalar_compare(op: str, type_: str) -> str:
    return f"""
static inline void stc_simd_{op}_{type_}({type_} * restrict a, const {type_} * restrict b, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        a[i] = ({cmp_scalar_expr[op]}) ? ({type_})~0 : ({type_})0;
    }}
}}
""".strip()


def resolve_typed_call(section: Any, type_: str) -> Optional[str]:
    if isinstance(section, dict):
        return section.get(type_)
    if isinstance(section, str):
        return section
    return None


def resolve_load_store(d: Dict[str, Any], type_: str) -> tuple[Optional[str], Optional[str]]:
    return resolve_typed_call(d["Load"], type_), resolve_typed_call(d["Store"], type_)


@dataclass
class FamilyBodyContext:
    backend: str
    backend_cfg: Dict[str, Any]
    type_name: str
    simd_type: str
    simd_cast: str
    lanes: str
    load_func: Optional[str]
    store_func: Optional[str]


@dataclass
class SimdFamilyRegistration:
    name: str
    backends: List[str]
    ops_per_type: Dict[str, List[str]]
    signature_emitter: Callable[[str, str], str]
    body_emitter: Callable[[str, str, FamilyBodyContext], Optional[str]]


builtin_family_registry: List[SimdFamilyRegistration] = []
custom_family_registry: List[SimdFamilyRegistration] = []
_builtin_families_registered = False


def register_simd_family(
    name: str,
    backend: str | List[str],
    ops_per_type: Dict[str, List[str]],
    signature_emitter: Callable[[str, str], str],
    body_emitter: Callable[[str, str, FamilyBodyContext], Optional[str]],
) -> None:
    """
    Register a new generated family without changing core emit loops.

    Example:
        register_simd_family(
            name="minmax",
            backend=["WASM", "SSE42", "AVX2"],
            ops_per_type={"i32": ["min", "max"], "f32": ["min", "max"]},
            signature_emitter=lambda op, ty:
                f"static inline void stc_simd_{op}_{ty}({ty} * restrict a, const {ty} * restrict b, const u64 len);",
            body_emitter=my_body_emitter,
        )
    """
    backends = [backend] if isinstance(backend, str) else list(backend)
    custom_family_registry.append(
        SimdFamilyRegistration(
            name=name,
            backends=backends,
            ops_per_type=ops_per_type,
            signature_emitter=signature_emitter,
            body_emitter=body_emitter,
        )
    )


def _all_families() -> List[SimdFamilyRegistration]:
    return builtin_family_registry + custom_family_registry


def emit_registered_family_signatures() -> List[str]:
    out: List[str] = []
    for family in _all_families():
        for type_, ops in family.ops_per_type.items():
            for op in ops:
                out.append(family.signature_emitter(op, type_))
    return out


def emit_registered_family_bodies(ctx: FamilyBodyContext) -> List[str]:
    out: List[str] = []
    for family in _all_families():
        if ctx.backend not in family.backends:
            continue
        for op in family.ops_per_type.get(ctx.type_name, []):
            body = family.body_emitter(op, ctx.type_name, ctx)
            if body:
                out.append(body)
    return out


def _emit_body_arith(op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    simd_op = ctx.backend_cfg["Arithmetic"].get(op, {}).get(type_name)
    if simd_op and ctx.load_func and ctx.store_func:
        return emit_stc_template_function_body_arith(
            op=op,
            type_=type_name,
            simd_type=ctx.simd_type,
            simd_store_func=ctx.store_func,
            simd_load_func=ctx.load_func,
            simd_op_func=simd_op,
            simd_op_symbol=ops_arith_symbol_mapping[op],
            simd_lanes=ctx.lanes,
            simd_cast=ctx.simd_cast,
        )
    return emit_scalar_binary(op, type_name, ops_arith_symbol_mapping[op])


def _emit_body_shift(op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    simd_op = ctx.backend_cfg.get("Shift", {}).get(op, {}).get(type_name)
    if simd_op and ctx.load_func and ctx.store_func:
        return emit_stc_template_function_body_shift(
            op=op,
            type_=type_name,
            simd_type=ctx.simd_type,
            simd_store_func=ctx.store_func,
            simd_load_func=ctx.load_func,
            simd_op_func=simd_op,
            simd_lanes=ctx.lanes,
            simd_cast=ctx.simd_cast,
            scalar_shift_expr=emit_shift_scalar_expr(op, type_name),
        )
    return emit_scalar_shift(op, type_name)


def _emit_body_logical_binary(op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    simd_op = resolve_typed_call(ctx.backend_cfg.get("Logical", {}).get(op), type_name)
    if simd_op and ctx.load_func and ctx.store_func:
        return emit_stc_template_function_body_logical_binary(
            op=op,
            type_=type_name,
            simd_type=ctx.simd_type,
            simd_store_func=ctx.store_func,
            simd_load_func=ctx.load_func,
            simd_op_func=simd_op,
            simd_lanes=ctx.lanes,
            simd_cast=ctx.simd_cast,
        )
    if op == "andnot":
        return f"""
static inline void stc_simd_andnot_{type_name}({type_name} * restrict a, const {type_name} * restrict b, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        a[i] = (~a[i]) & b[i];
    }}
}}
""".strip()
    return emit_scalar_binary(op, type_name, ops_bit_symbol_mapping[op])


def _emit_body_logical_unary(op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    simd_op = resolve_typed_call(ctx.backend_cfg.get("Logical", {}).get(op), type_name)
    if simd_op and ctx.load_func and ctx.store_func:
        return emit_stc_template_function_body_logical_unary(
            op=op,
            type_=type_name,
            simd_type=ctx.simd_type,
            simd_store_func=ctx.store_func,
            simd_load_func=ctx.load_func,
            simd_op_func=simd_op,
            simd_lanes=ctx.lanes,
            simd_cast=ctx.simd_cast,
            scalar_symbol=ops_bit_symbol_mapping[op],
        )
    return emit_scalar_unary(op, type_name, ops_bit_symbol_mapping[op])


def _emit_body_compare(op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    simd_op = ctx.backend_cfg.get("Compare", {}).get(op, {}).get(type_name)
    if simd_op and simd_op != "_mm256_cmp_ps" and ctx.load_func and ctx.store_func:
        return emit_stc_template_function_body_compare(
            op=op,
            type_=type_name,
            simd_type=ctx.simd_type,
            simd_store_func=ctx.store_func,
            simd_load_func=ctx.load_func,
            simd_op_func=simd_op,
            simd_lanes=ctx.lanes,
            simd_cast=ctx.simd_cast,
            scalar_cmp_expr=cmp_scalar_expr[op],
        )
    return emit_scalar_compare(op, type_name)


def _emit_body_splat(_op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    splat_op = ctx.backend_cfg.get("Set", {}).get("splat", {}).get(type_name)
    if splat_op and ctx.store_func:
        return emit_stc_template_function_body_splat(
            type_=type_name,
            simd_type=ctx.simd_type,
            simd_store_func=ctx.store_func,
            simd_set_func=splat_op,
            simd_lanes=ctx.lanes,
            simd_cast=ctx.simd_cast,
        )
    return f"""
static inline void stc_simd_splat_{type_name}({type_name} * restrict a, const {type_name} value, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        a[i] = value;
    }}
}}
""".strip()


def _emit_body_bitmask(_op: str, type_name: str, _ctx: FamilyBodyContext) -> Optional[str]:
    return f"""
static inline u64 stc_simd_bitmask_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    u64 out_mask = 0;
    u64 shift = 0;
    for (u64 i = 0; i < len; ++i) {{
        out_mask |= ((u64)(a[i] != 0) << shift);
        ++shift;
    }}
    return out_mask;
}}
""".strip()


def _emit_body_all_true(_op: str, type_name: str, _ctx: FamilyBodyContext) -> Optional[str]:
    if _ctx.backend == "WASM" and _ctx.load_func:
        wasm_all_true_fn = {
            "i8": "wasm_i8x16_all_true",
            "i16": "wasm_i16x8_all_true",
            "i32": "wasm_i32x4_all_true",
            "i64": "wasm_i64x2_all_true",
        }.get(type_name)

        if type_name == "f32":
            return f"""
static inline bool stc_simd_all_true_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    const u64 width = {_ctx.lanes};
    u64 i = 0;
    const simd_f32 vz = wasm_f32x4_splat(0.0f);

    for (; (i + width) <= len; i += width) {{
        simd_f32 va = {_ctx.load_func}((const {_ctx.simd_cast}*)(a + i));
        simd_i32 mask = wasm_f32x4_ne(va, vz);
        if (!wasm_i32x4_all_true(mask)) return false;
    }}

    for (; i < len; ++i) {{
        if (!a[i]) return false;
    }}

    return true;
}}
""".strip()

        if wasm_all_true_fn:
            return f"""
static inline bool stc_simd_all_true_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    const u64 width = {_ctx.lanes};
    u64 i = 0;

    for (; (i + width) <= len; i += width) {{
        simd_{type_name} va = {_ctx.load_func}((const {_ctx.simd_cast}*)(a + i));
        if (!{wasm_all_true_fn}(va)) return false;
    }}

    for (; i < len; ++i) {{
        if (!a[i]) return false;
    }}

    return true;
}}
""".strip()

    return f"""
static inline bool stc_simd_all_true_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        if (!a[i]) return false;
    }}
    return true;
}}
""".strip()


def _emit_body_any_true(_op: str, type_name: str, _ctx: FamilyBodyContext) -> Optional[str]:
    if _ctx.backend == "WASM" and _ctx.load_func:
        if type_name == "f32":
            return f"""
static inline bool stc_simd_any_true_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    const u64 width = {_ctx.lanes};
    u64 i = 0;
    const simd_f32 vz = wasm_f32x4_splat(0.0f);

    for (; (i + width) <= len; i += width) {{
        simd_f32 va = {_ctx.load_func}((const {_ctx.simd_cast}*)(a + i));
        simd_i32 mask = wasm_f32x4_ne(va, vz);
        if (wasm_v128_any_true(mask)) return true;
    }}

    for (; i < len; ++i) {{
        if (a[i]) return true;
    }}

    return false;
}}
""".strip()

        return f"""
static inline bool stc_simd_any_true_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    const u64 width = {_ctx.lanes};
    u64 i = 0;

    for (; (i + width) <= len; i += width) {{
        simd_{type_name} va = {_ctx.load_func}((const {_ctx.simd_cast}*)(a + i));
        if (wasm_v128_any_true(va)) return true;
    }}

    for (; i < len; ++i) {{
        if (a[i]) return true;
    }}

    return false;
}}
""".strip()

    return f"""
static inline bool stc_simd_any_true_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        if (a[i]) return true;
    }}
    return false;
}}
""".strip()

def _emit_body_minmax(op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    simd_op = ctx.backend_cfg.get("MinMax", {}).get(op, {}).get(type_name)
    scalar_expr = {
        "min": "a[i] < b[i] ? a[i] : b[i]",
        "max": "a[i] > b[i] ? a[i] : b[i]",
    }[op]
    if simd_op and ctx.load_func and ctx.store_func:
        return emit_stc_template_function_body_minmax(
            op=op,
            type_=type_name,
            simd_type=ctx.simd_type,
            simd_store_func=ctx.store_func,
            simd_load_func=ctx.load_func,
            simd_op_func=simd_op,
            simd_lanes=ctx.lanes,
            simd_cast=ctx.simd_cast,
            scalar_expr=scalar_expr,
        )
    return f"""
static inline void stc_simd_{op}_{type_name}({type_name} * restrict a, const {type_name} * restrict b, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        a[i] = {scalar_expr};
    }}
}}
""".strip()


def _emit_body_count_true(_op: str, type_name: str, _ctx: FamilyBodyContext) -> Optional[str]:
    return f"""
static inline u64 stc_simd_count_true_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {{
        ct += (u64)(a[i] != 0);
    }}
    return ct;
}}
""".strip()


def _emit_body_first_true(_op: str, type_name: str, _ctx: FamilyBodyContext) -> Optional[str]:
    return f"""
static inline u64 stc_simd_first_true_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        if (a[i] != 0) return i;
    }}
    return (u64)-1;
}}
""".strip()


def _emit_body_count_compare_scalar(op: str, type_name: str, _ctx: FamilyBodyContext) -> Optional[str]:
    cmp_expr = cmp_scalar_expr[op].replace("b[i]", "value")
    return f"""
static inline u64 stc_simd_count_{op}_scalar_{type_name}(const {type_name} * restrict a, const {type_name} value, const u64 len)
{{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {{
        ct += (u64)({cmp_expr});
    }}
    return ct;
}}
""".strip()


def _emit_body_first_compare_scalar(op: str, type_name: str, _ctx: FamilyBodyContext) -> Optional[str]:
    cmp_expr = cmp_scalar_expr[op].replace("b[i]", "value")
    return f"""
static inline u64 stc_simd_first_{op}_scalar_{type_name}(const {type_name} * restrict a, const {type_name} value, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        if ({cmp_expr}) return i;
    }}
    return (u64)-1;
}}
""".strip()


def _sig_from_type_only(sig_fn: Callable[[str], str]) -> Callable[[str, str], str]:
    return lambda _op, ty: sig_fn(ty)


def _register_builtin_families() -> None:
    global _builtin_families_registered
    if _builtin_families_registered:
        return

    all_backends = ["WASM", "SSE42", "AVX2"]
    builtin_family_registry.extend([
        SimdFamilyRegistration(
            name="arith",
            backends=all_backends,
            ops_per_type=ops_arith_per_type,
            signature_emitter=emit_stc_template_function_signature_arith,
            body_emitter=_emit_body_arith,
        ),
        SimdFamilyRegistration(
            name="shift",
            backends=all_backends,
            ops_per_type=ops_shift_per_type,
            signature_emitter=emit_stc_template_function_signature_shift,
            body_emitter=_emit_body_shift,
        ),
        SimdFamilyRegistration(
            name="logical_binary",
            backends=all_backends,
            ops_per_type=ops_logical_binary_per_type,
            signature_emitter=emit_stc_template_function_signature_logical_binary,
            body_emitter=_emit_body_logical_binary,
        ),
        SimdFamilyRegistration(
            name="logical_unary",
            backends=all_backends,
            ops_per_type=ops_logical_unary_per_type,
            signature_emitter=emit_stc_template_function_signature_logical_unary,
            body_emitter=_emit_body_logical_unary,
        ),
        SimdFamilyRegistration(
            name="compare",
            backends=all_backends,
            ops_per_type=ops_compare_per_type,
            signature_emitter=emit_stc_template_function_signature_compare,
            body_emitter=_emit_body_compare,
        ),
        SimdFamilyRegistration(
            name="splat",
            backends=all_backends,
            ops_per_type=ops_set_splat_per_type,
            signature_emitter=_sig_from_type_only(emit_stc_template_function_signature_set_splat),
            body_emitter=_emit_body_splat,
        ),
        SimdFamilyRegistration(
            name="bitmask",
            backends=all_backends,
            ops_per_type=ops_bitmask_per_type,
            signature_emitter=_sig_from_type_only(emit_stc_template_function_signature_bitmask),
            body_emitter=_emit_body_bitmask,
        ),
        SimdFamilyRegistration(
            name="all_true",
            backends=all_backends,
            ops_per_type=ops_all_true_per_type,
            signature_emitter=_sig_from_type_only(emit_stc_template_function_signature_all_true),
            body_emitter=_emit_body_all_true,
        ),
        SimdFamilyRegistration(
            name="any_true",
            backends=all_backends,
            ops_per_type=ops_any_true_per_type,
            signature_emitter=_sig_from_type_only(emit_stc_template_function_signature_any_true),
            body_emitter=_emit_body_any_true,
        ),
        SimdFamilyRegistration(
            name="minmax",
            backends=all_backends,
            ops_per_type=ops_minmax_per_type,
            signature_emitter=emit_stc_template_function_signature_arith,
            body_emitter=_emit_body_minmax,
        ),
        SimdFamilyRegistration(
            name="count_true",
            backends=all_backends,
            ops_per_type=ops_count_true_per_type,
            signature_emitter=_sig_from_type_only(emit_stc_template_function_signature_count_true),
            body_emitter=_emit_body_count_true,
        ),
        SimdFamilyRegistration(
            name="first_true",
            backends=all_backends,
            ops_per_type=ops_first_true_per_type,
            signature_emitter=_sig_from_type_only(emit_stc_template_function_signature_first_true),
            body_emitter=_emit_body_first_true,
        ),
        SimdFamilyRegistration(
            name="count_compare_scalar",
            backends=all_backends,
            ops_per_type=ops_count_compare_scalar_per_type,
            signature_emitter=emit_stc_template_function_signature_count_compare_scalar,
            body_emitter=_emit_body_count_compare_scalar,
        ),
        SimdFamilyRegistration(
            name="first_compare_scalar",
            backends=all_backends,
            ops_per_type=ops_first_compare_scalar_per_type,
            signature_emitter=emit_stc_template_function_signature_first_compare_scalar,
            body_emitter=_emit_body_first_compare_scalar,
        ),
    ])

    _builtin_families_registered = True


def emit_signatures() -> List[str]:
    _register_builtin_families()
    return emit_registered_family_signatures()


def emit_backend_bodies(backend: str, d: Dict[str, Any]) -> List[str]:
    _register_builtin_families()
    out: List[str] = []
    for type_name in simd_type_order:
        load_func, store_func = resolve_load_store(d, type_name)
        family_ctx = FamilyBodyContext(
            backend=backend,
            backend_cfg=d,
            type_name=type_name,
            simd_type=type_to_simd[type_name],
            simd_cast=emit_simd_cast(type_name),
            lanes=str(lanes(backend, type_name)),
            load_func=load_func,
            store_func=store_func,
        )
        out.extend(emit_registered_family_bodies(family_ctx))
    return out


def build_header_text() -> str:
    parts: List[str] = []
    parts.append("#pragma once")
    parts.append("")
    parts.append("#if defined(__wasm_simd128__)")
    parts.append("#define LANES_U8\t16")
    parts.append("#define LANES_U16\t8")
    parts.append("#define LANES_U32\t4")
    parts.append("#define LANES_U64\t2")
    parts.append("#define LANES_I8\t16")
    parts.append("#define LANES_I16\t8")
    parts.append("#define LANES_I32\t4")
    parts.append("#define LANES_I64\t2")
    parts.append("#define LANES_F32\t4")
    parts.append("#elif defined(__AVX2__)")
    parts.append("#define LANES_U8\t32")
    parts.append("#define LANES_U16\t16")
    parts.append("#define LANES_U32\t8")
    parts.append("#define LANES_U64\t4")
    parts.append("#define LANES_I8\t32")
    parts.append("#define LANES_I16\t16")
    parts.append("#define LANES_I32\t8")
    parts.append("#define LANES_I64\t4")
    parts.append("#define LANES_F32\t8")
    parts.append("#elif defined(__SSE4_2__)")
    parts.append("#define LANES_U8\t16")
    parts.append("#define LANES_U16\t8")
    parts.append("#define LANES_U32\t4")
    parts.append("#define LANES_U64\t2")
    parts.append("#define LANES_I8\t16")
    parts.append("#define LANES_I16\t8")
    parts.append("#define LANES_I32\t4")
    parts.append("#define LANES_I64\t2")
    parts.append("#define LANES_F32\t4")
    parts.append("#else")
    parts.append('#  error "No SIMD backend enabled"')
    parts.append("#endif")
    parts.append("")
    parts.extend(emit_signatures())
    parts.append("")
    ordered_backends = ["WASM", "AVX2", "SSE42"]
    for idx, backend in enumerate(ordered_backends):
        cond = backend_guards[backend].replace("#if defined(", "").replace(")", "")
        if idx == 0:
            parts.append(f"#if defined({cond})")
        else:
            parts.append(f"#elif defined({cond})")
        parts.extend(emit_backend_bodies(backend, backend_emitteer[backend]))
        parts.append("")
    parts.append("#endif")
    parts.append("")
    return "\n".join(parts).rstrip() + "\n"




if __name__ == "__main__":
    text = build_header_text()
    with open("stc_simd_codegen.h", "w", encoding="utf-8") as f:
        f.write(text)
    print(text)
