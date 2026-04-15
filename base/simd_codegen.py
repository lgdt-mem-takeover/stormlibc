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


def emit_simd_cast(type_: str) -> str:
    cast_ty: str = simd_cast_mapping[type_];
    return cast_ty;

def lanes(backend, type_) -> int:
    return backend_bits[backend] // (type_sizes[type_] * 8);

def lane_macro(type_: str) -> str:
    return {
        "i8": "LANES_I8",
        "i16": "LANES_I16",
        "i32": "LANES_I32",
        "i64": "LANES_I64",
        "f32": "LANES_F32",
    }[type_]

def emit_stc_template_function_signature_arith(op: str, type_: str) -> str:
    return f"static inline {type_} *stc_simd_{op}_{type_}({type_} * restrict out, const {type_} * restrict a, const {type_} * restrict b, const u64 len);";

def emit_stc_template_function_signature_logical_binary(op: str, type_: str) -> str:
    return f"static inline {type_} *stc_simd_{op}_{type_}({type_} * restrict out, const {type_} * restrict a, const {type_} * restrict b, const u64 len);"

def emit_stc_template_function_signature_logical_unary(op: str, type_: str) -> str:
    return f"static inline {type_} *stc_simd_{op}_{type_}({type_} * restrict out, const {type_} * restrict a, const u64 len);"

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
    return f"static inline {type_} *stc_simd_splat_{type_}({type_} * restrict out, const {type_} value, const u64 len);"

def emit_stc_template_function_signature_shift(op: str, type_: str) -> str:
    return f"static inline {type_} *stc_simd_{op}_{type_}({type_} * restrict out, const {type_} * restrict a, const u32 shift_by, const u64 len);"

def emit_stc_template_function_signature_compare(op: str, type_: str) -> str:
    return f"static inline {type_} *stc_simd_{op}_{type_}({type_} * restrict out, const {type_} * restrict a, const {type_} * restrict b, const u64 len);"

def emit_stc_template_function_signature_reduce(op: str, type_: str) -> str:
    return f"static inline {type_} stc_simd_reduce_{op}_{type_}(const {type_} * restrict a, const u64 len);"


def emit_slice_binary_body(
    op: str,
    type_: str,
    simd_type: str,
    load_func: str,
    store_func: str,
    simd_cast: str,
    lanes_value: int,
    simd_expr: Optional[str],
    scalar_tail: str,
    prelude: str = "",
) -> str:
    if simd_expr and load_func and store_func:
        prelude_block = f"{prelude}\n" if prelude else ""
        return f"""
static inline {type_} *stc_simd_{op}_{type_}({type_} * restrict out, const {type_} * restrict a, const {type_} * restrict b, const u64 len)
{{
    const u64 width = {lanes_value};
    u64 rem = len % width;
    u64 i = 0;
{prelude_block}    for (; (i + width) <= len; i += width) {{
        {simd_type} va = {load_func}((const {simd_cast}*)(a + i));
        {simd_type} vb = {load_func}((const {simd_cast}*)(b + i));
        {simd_type} vr = {simd_expr};
        {store_func}(({simd_cast}*)(out + i), vr);
    }}

    while (rem) {{
{scalar_tail}
        ++i;
        --rem;
    }}

    return out;
}}
""".strip()
    return f"""
static inline {type_} *stc_simd_{op}_{type_}({type_} * restrict out, const {type_} * restrict a, const {type_} * restrict b, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
{scalar_tail}
    }}
    return out;
}}
""".strip()


def emit_slice_unary_body(
    op: str,
    type_: str,
    simd_type: str,
    load_func: str,
    store_func: str,
    simd_cast: str,
    lanes_value: int,
    simd_expr: Optional[str],
    scalar_tail: str,
) -> str:
    if simd_expr and load_func and store_func:
        return f"""
static inline {type_} *stc_simd_{op}_{type_}({type_} * restrict out, const {type_} * restrict a, const u64 len)
{{
    const u64 width = {lanes_value};
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {{
        {simd_type} va = {load_func}((const {simd_cast}*)(a + i));
        {simd_type} vr = {simd_expr};
        {store_func}(({simd_cast}*)(out + i), vr);
    }}

    while (rem) {{
{scalar_tail}
        ++i;
        --rem;
    }}

    return out;
}}
""".strip()
    return f"""
static inline {type_} *stc_simd_{op}_{type_}({type_} * restrict out, const {type_} * restrict a, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
{scalar_tail}
    }}
    return out;
}}
""".strip()


def emit_slice_shift_body(
    op: str,
    type_: str,
    simd_type: str,
    load_func: str,
    store_func: str,
    simd_cast: str,
    lanes_value: int,
    simd_expr: Optional[str],
    scalar_tail: str,
) -> str:
    if simd_expr and load_func and store_func:
        return f"""
static inline {type_} *stc_simd_{op}_{type_}({type_} * restrict out, const {type_} * restrict a, const u32 shift_by, const u64 len)
{{
    const u64 width = {lanes_value};
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {{
        {simd_type} va = {load_func}((const {simd_cast}*)(a + i));
        {simd_type} vr = {simd_expr};
        {store_func}(({simd_cast}*)(out + i), vr);
    }}

    while (rem) {{
{scalar_tail}
        ++i;
        --rem;
    }}

    return out;
}}
""".strip()
    return f"""
static inline {type_} *stc_simd_{op}_{type_}({type_} * restrict out, const {type_} * restrict a, const u32 shift_by, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
{scalar_tail}
    }}
    return out;
}}
""".strip()


def emit_slice_splat_body(
    type_: str,
    simd_type: str,
    store_func: str,
    simd_cast: str,
    lanes_value: int,
    simd_expr: Optional[str],
) -> str:
    if simd_expr and store_func:
        return f"""
static inline {type_} *stc_simd_splat_{type_}({type_} * restrict out, const {type_} value, const u64 len)
{{
    const u64 width = {lanes_value};
    u64 rem = len % width;
    u64 i = 0;
    const {simd_type} vv = {simd_expr};
    for (; (i + width) <= len; i += width) {{
        {store_func}(({simd_cast}*)(out + i), vv);
    }}

    while (rem) {{
        out[i] = value;
        ++i;
        --rem;
    }}

    return out;
}}
""".strip()
    return f"""
static inline {type_} *stc_simd_splat_{type_}({type_} * restrict out, const {type_} value, const u64 len)
{{
    for (u64 i = 0; i < len; ++i) {{
        out[i] = value;
    }}
    return out;
}}
""".strip()


def emit_register_binary_body(op: str, type_: str, simd_type: str, simd_expr: str) -> str:
    return f"""
static inline {simd_type} stc_simd_{op}_{type_}(const {simd_type} a, const {simd_type} b)
{{
    return {simd_expr};
}}
""".strip()


def emit_register_unary_body(op: str, type_: str, simd_type: str, simd_expr: str) -> str:
    return f"""
static inline {simd_type} stc_simd_{op}_{type_}(const {simd_type} a)
{{
    return {simd_expr};
}}
""".strip()


def emit_register_shift_body(op: str, type_: str, simd_type: str, simd_expr: str) -> str:
    return f"""
static inline {simd_type} stc_simd_{op}_{type_}(const {simd_type} a, const u32 shift_by)
{{
    return {simd_expr};
}}
""".strip()


def emit_register_splat_body(type_: str, simd_type: str, simd_expr: str) -> str:
    return f"""
static inline {simd_type} stc_simd_splat_{type_}(const {type_} value)
{{
    return {simd_expr};
}}
""".strip()


def emit_register_binary_scalar_fallback(
    op: str,
    type_: str,
    simd_type: str,
    lanes_macro: str,
    scalar_stmt: str,
    compare_f32_bits: Optional[str] = None,
) -> str:
    if type_ == "f32" and compare_f32_bits:
        lane_body = f"""
        union {{ u32 u; f32 f; }} ur;
        ur.u = {compare_f32_bits};
        tr[i] = ur.f;"""
    elif type_ == "f32":
        lane_body = f"""
        union {{ u32 u; f32 f; }} ua, ub, ur;
        ua.f = ta[i];
        ub.f = tb[i];
        ur.u = {scalar_stmt};
        tr[i] = ur.f;"""
    else:
        lane_body = f"""
        tr[i] = {scalar_stmt};"""
    return f"""
static inline {simd_type} stc_simd_{op}_{type_}(const {simd_type} a, const {simd_type} b)
{{
    __attribute__((aligned(STC_SIMD_ALIGN))) {type_} ta[{lanes_macro}];
    __attribute__((aligned(STC_SIMD_ALIGN))) {type_} tb[{lanes_macro}];
    __attribute__((aligned(STC_SIMD_ALIGN))) {type_} tr[{lanes_macro}];

    stc_simd_store_{type_}(ta, a);
    stc_simd_store_{type_}(tb, b);

    for (u64 i = 0; i < {lanes_macro}; ++i) {{{lane_body}
    }}

    return stc_simd_load_{type_}(tr);
}}
""".strip()


def emit_register_unary_scalar_fallback(
    op: str,
    type_: str,
    simd_type: str,
    lanes_macro: str,
    scalar_stmt: str,
) -> str:
    if type_ == "f32":
        lane_body = f"""
        union {{ u32 u; f32 f; }} ua, ur;
        ua.f = ta[i];
        ur.u = {scalar_stmt};
        tr[i] = ur.f;"""
    else:
        lane_body = f"""
        tr[i] = {scalar_stmt};"""
    return f"""
static inline {simd_type} stc_simd_{op}_{type_}(const {simd_type} a)
{{
    __attribute__((aligned(STC_SIMD_ALIGN))) {type_} ta[{lanes_macro}];
    __attribute__((aligned(STC_SIMD_ALIGN))) {type_} tr[{lanes_macro}];

    stc_simd_store_{type_}(ta, a);

    for (u64 i = 0; i < {lanes_macro}; ++i) {{{lane_body}
    }}

    return stc_simd_load_{type_}(tr);
}}
""".strip()


def emit_register_shift_scalar_fallback(
    op: str,
    type_: str,
    simd_type: str,
    lanes_macro: str,
    scalar_expr: str,
) -> str:
    return f"""
static inline {simd_type} stc_simd_{op}_{type_}(const {simd_type} a, const u32 shift_by)
{{
    __attribute__((aligned(STC_SIMD_ALIGN))) {type_} ta[{lanes_macro}];
    __attribute__((aligned(STC_SIMD_ALIGN))) {type_} tr[{lanes_macro}];

    stc_simd_store_{type_}(ta, a);

    for (u64 i = 0; i < {lanes_macro}; ++i) {{
        tr[i] = {scalar_expr};
    }}

    return stc_simd_load_{type_}(tr);
}}
""".strip()


def emit_register_splat_scalar_fallback(
    type_: str,
    simd_type: str,
    lanes_macro: str,
) -> str:
    return f"""
static inline {simd_type} stc_simd_splat_{type_}(const {type_} value)
{{
    __attribute__((aligned(STC_SIMD_ALIGN))) {type_} tr[{lanes_macro}];
    for (u64 i = 0; i < {lanes_macro}; ++i) {{
        tr[i] = value;
    }}
    return stc_simd_load_{type_}(tr);
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
    "i64": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
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
    "i64": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "f32": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
}

ops_first_compare_scalar_per_type: Dict[str, List[str]] = {
    "i8": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i16": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i32": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "i64": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
    "f32": ["cmpeq", "cmpne", "cmplt", "cmpgt", "cmple", "cmpge"],
}

ops_reduce_per_type: Dict[str, List[str]] = {
    "i8": ["add"],
    "i16": ["add", "mul"],
    "i32": ["add", "mul", "min", "max"],
    "i64": ["add"],
    "f32": ["add", "mul", "min", "max"],
}


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
    return emit_slice_binary_body(
        op=op,
        type_=type_name,
        simd_type=ctx.simd_type,
        load_func=ctx.load_func,
        store_func=ctx.store_func,
        simd_cast=ctx.simd_cast,
        lanes_value=ctx.lanes,
        simd_expr=f"{simd_op}(va, vb)" if simd_op else None,
        scalar_tail=f"        out[i] = a[i] {ops_arith_symbol_mapping[op]} b[i];",
    )


def _emit_body_shift(op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    simd_op = ctx.backend_cfg.get("Shift", {}).get(op, {}).get(type_name)
    return emit_slice_shift_body(
        op=op,
        type_=type_name,
        simd_type=ctx.simd_type,
        load_func=ctx.load_func,
        store_func=ctx.store_func,
        simd_cast=ctx.simd_cast,
        lanes_value=ctx.lanes,
        simd_expr=f"{simd_op}(va, shift_by)" if simd_op else None,
        scalar_tail=f"        out[i] = {emit_shift_scalar_expr(op, type_name)};",
    )


def _emit_body_logical_binary(op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    simd_op = resolve_typed_call(ctx.backend_cfg.get("Logical", {}).get(op), type_name)
    if type_name == "f32":
        scalar_tail = {
            "and": """        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u & ub.u;
        out[i] = ur.f;""",
            "or": """        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u | ub.u;
        out[i] = ur.f;""",
            "xor": """        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u ^ ub.u;
        out[i] = ur.f;""",
            "andnot": """        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = (~ua.u) & ub.u;
        out[i] = ur.f;""",
        }[op]
    elif op == "andnot":
        scalar_tail = "        out[i] = (~a[i]) & b[i];"
    else:
        scalar_tail = f"        out[i] = a[i] {ops_bit_symbol_mapping[op]} b[i];"
    return emit_slice_binary_body(
        op=op,
        type_=type_name,
        simd_type=ctx.simd_type,
        load_func=ctx.load_func,
        store_func=ctx.store_func,
        simd_cast=ctx.simd_cast,
        lanes_value=ctx.lanes,
        simd_expr=f"{simd_op}(va, vb)" if simd_op else None,
        scalar_tail=scalar_tail,
    )


def _emit_body_logical_unary(op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    simd_op = resolve_typed_call(ctx.backend_cfg.get("Logical", {}).get(op), type_name)
    scalar_tail = """        union { u32 u; f32 f; } ua, ur;
        ua.f = a[i];
        ur.u = ~ua.u;
        out[i] = ur.f;""" if type_name == "f32" else f"        out[i] = {ops_bit_symbol_mapping[op]}a[i];"
    return emit_slice_unary_body(
        op=op,
        type_=type_name,
        simd_type=ctx.simd_type,
        load_func=ctx.load_func,
        store_func=ctx.store_func,
        simd_cast=ctx.simd_cast,
        lanes_value=ctx.lanes,
        simd_expr=f"{simd_op}(va)" if simd_op else None,
        scalar_tail=scalar_tail,
    )


def _emit_body_compare(op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    simd_expr, prelude = _compare_expr_scalar_reducer(op, type_name, ctx, "va", "vb")
    scalar_tail = f"        out[i] = ({cmp_scalar_expr[op]}) ? ({type_name})~0 : ({type_name})0;"
    if type_name == "f32":
        scalar_tail = f"""        union {{ u32 u; f32 f; }} ur;
        ur.u = ({cmp_scalar_expr[op]}) ? 0xffffffffu : 0u;
        out[i] = ur.f;"""
    return emit_slice_binary_body(
        op=op,
        type_=type_name,
        simd_type=ctx.simd_type,
        load_func=ctx.load_func,
        store_func=ctx.store_func,
        simd_cast=ctx.simd_cast,
        lanes_value=ctx.lanes,
        simd_expr=simd_expr,
        scalar_tail=scalar_tail,
        prelude=prelude,
    )


def _emit_body_splat(_op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    splat_op = ctx.backend_cfg.get("Set", {}).get("splat", {}).get(type_name)
    return emit_slice_splat_body(
        type_=type_name,
        simd_type=ctx.simd_type,
        store_func=ctx.store_func,
        simd_cast=ctx.simd_cast,
        lanes_value=ctx.lanes,
        simd_expr=f"{splat_op}(value)" if splat_op else None,
    )


def _emit_body_bitmask(_op: str, type_name: str, _ctx: FamilyBodyContext) -> Optional[str]:
    if type_name == "f32":
        return f"""
static inline u64 stc_simd_bitmask_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {{
        union {{ f32 f; u32 u; }} bits;
        bits.f = a[i];
        out_mask |= ((u64)((bits.u >> 31) & 1u) << i);
    }}
    return out_mask;
}}
""".strip()
    type_bits = type_sizes[type_name] * 8
    unsigned_type = {
        "i8": "u8",
        "i16": "u16",
        "i32": "u32",
        "i64": "u64",
    }[type_name]
    return f"""
static inline u64 stc_simd_bitmask_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {{
        out_mask |= ((u64)(((({unsigned_type})a[i]) >> ({type_bits} - 1)) & 1u) << i);
    }}
    return out_mask;
}}
""".strip()


def _emit_body_all_true(_op: str, type_name: str, _ctx: FamilyBodyContext) -> Optional[str]:
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
    scalar_tail = {
        "min": "        out[i] = a[i] < b[i] ? a[i] : b[i];",
        "max": "        out[i] = a[i] > b[i] ? a[i] : b[i];",
    }[op]
    return emit_slice_binary_body(
        op=op,
        type_=type_name,
        simd_type=ctx.simd_type,
        load_func=ctx.load_func,
        store_func=ctx.store_func,
        simd_cast=ctx.simd_cast,
        lanes_value=ctx.lanes,
        simd_expr=f"{simd_op}(va, vb)" if simd_op else None,
        scalar_tail=scalar_tail,
    )


def _emit_body_reduce(op: str, type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    vector_op = None
    if op in ("add", "mul"):
        vector_op = ctx.backend_cfg.get("Arithmetic", {}).get(op, {}).get(type_name)
    else:
        vector_op = ctx.backend_cfg.get("MinMax", {}).get(op, {}).get(type_name)

    scalar_seed_expr = {
        "add": f"({type_name})0",
        "mul": f"({type_name})1",
        "min": f"({type_name})0",
        "max": f"({type_name})0",
    }[op]
    scalar_fold_expr = {
        "add": "acc + tmp[lane]",
        "mul": "acc * tmp[lane]",
        "min": "acc < tmp[lane] ? acc : tmp[lane]",
        "max": "acc > tmp[lane] ? acc : tmp[lane]",
    }[op]
    start_index = "1" if op in ("min", "max") else "0"
    init_acc = f"    {type_name} acc = a[0];\n" if op in ("min", "max") else f"    {type_name} acc = {scalar_seed_expr};\n"

    if vector_op and ctx.load_func and ctx.store_func:
        vector_init = {
            "add": resolve_typed_call(ctx.backend_cfg.get("Set", {}).get("set1"), type_name) if ctx.backend != "WASM" else ctx.backend_cfg.get("Set", {}).get("splat", {}).get(type_name),
            "mul": resolve_typed_call(ctx.backend_cfg.get("Set", {}).get("set1"), type_name) if ctx.backend != "WASM" else ctx.backend_cfg.get("Set", {}).get("splat", {}).get(type_name),
            "min": resolve_typed_call(ctx.backend_cfg.get("Set", {}).get("set1"), type_name) if ctx.backend != "WASM" else ctx.backend_cfg.get("Set", {}).get("splat", {}).get(type_name),
            "max": resolve_typed_call(ctx.backend_cfg.get("Set", {}).get("set1"), type_name) if ctx.backend != "WASM" else ctx.backend_cfg.get("Set", {}).get("splat", {}).get(type_name),
        }[op]
        if vector_init:
            init_value = "a[0]" if op in ("min", "max") else ("1" if op == "mul" else "0")
            return f"""
static inline {type_name} stc_simd_reduce_{op}_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    if (!len) return {scalar_seed_expr};

    const u64 width = {ctx.lanes};
    u64 i = {start_index};
    __attribute__((aligned(STC_SIMD_ALIGN))) {type_name} tmp[{lane_macro(type_name)}];
    {ctx.simd_type} vacc = {vector_init}({init_value});

    for (; (i + width) <= len; i += width) {{
        {ctx.simd_type} va = {ctx.load_func}((const {ctx.simd_cast}*)(a + i));
        vacc = {vector_op}(vacc, va);
    }}

    {ctx.store_func}(({ctx.simd_cast}*)tmp, vacc);
{init_acc}    for (u64 lane = 0; lane < {lane_macro(type_name)}; ++lane) {{
        acc = {scalar_fold_expr};
    }}

    for (; i < len; ++i) {{
        acc = {scalar_fold_expr.replace('tmp[lane]', 'a[i]')};
    }}

    return acc;
}}
""".strip()

    scalar_init = f"    {type_name} acc = a[0];\n    for (u64 i = 1; i < len; ++i) {{\n        acc = {scalar_fold_expr.replace('tmp[lane]', 'a[i]')};\n    }}" if op in ("min", "max") else f"    {type_name} acc = {scalar_seed_expr};\n    for (u64 i = 0; i < len; ++i) {{\n        acc = {scalar_fold_expr.replace('tmp[lane]', 'a[i]')};\n    }}"
    return f"""
static inline {type_name} stc_simd_reduce_{op}_{type_name}(const {type_name} * restrict a, const u64 len)
{{
    if (!len) return {scalar_seed_expr};
{scalar_init}
    return acc;
}}
""".strip()


def _compare_expr_scalar_reducer(
    op: str,
    type_name: str,
    ctx: FamilyBodyContext,
    va_name: str,
    vv_name: str,
) -> tuple[Optional[str], str]:
    if ctx.backend == "AVX2" and type_name == "f32":
        imm_by_op = {
            "cmpeq": "_CMP_EQ_OQ",
            "cmpne": "_CMP_NEQ_OQ",
            "cmplt": "_CMP_LT_OQ",
            "cmpgt": "_CMP_GT_OQ",
            "cmple": "_CMP_LE_OQ",
            "cmpge": "_CMP_GE_OQ",
        }
        return f"_mm256_cmp_ps({va_name}, {vv_name}, {imm_by_op[op]})", ""

    if ctx.backend == "SSE42" and type_name == "f32":
        sse_f32_cmp = {
            "cmpeq": "_mm_cmpeq_ps",
            "cmpne": "_mm_cmpneq_ps",
            "cmplt": "_mm_cmplt_ps",
            "cmpgt": "_mm_cmpgt_ps",
            "cmple": "_mm_cmple_ps",
            "cmpge": "_mm_cmpge_ps",
        }
        return f"{sse_f32_cmp[op]}({va_name}, {vv_name})", ""

    simd_op = ctx.backend_cfg.get("Compare", {}).get(op, {}).get(type_name)
    if simd_op:
        return f"{simd_op}({va_name}, {vv_name})", ""

    if ctx.backend in ("SSE42", "AVX2") and type_name != "f32":
        eq_fn = ctx.backend_cfg.get("Compare", {}).get("cmpeq", {}).get(type_name)
        gt_fn = ctx.backend_cfg.get("Compare", {}).get("cmpgt", {}).get(type_name)
        xor_fn = ctx.backend_cfg.get("Logical", {}).get("xor", {}).get(type_name)
        set1_fn = ctx.backend_cfg.get("Set", {}).get("set1", {}).get(type_name)
        if op == "cmpeq" and eq_fn:
            return f"{eq_fn}({va_name}, {vv_name})", ""
        if op == "cmpgt" and gt_fn:
            return f"{gt_fn}({va_name}, {vv_name})", ""
        if gt_fn and eq_fn and xor_fn and set1_fn:
            prelude = f"    const {ctx.simd_type} all_ones = {set1_fn}(-1);"
            if op == "cmplt":
                return f"{gt_fn}({vv_name}, {va_name})", ""
            if op == "cmpne":
                return f"{xor_fn}({eq_fn}({va_name}, {vv_name}), all_ones)", prelude
            if op == "cmple":
                return f"{xor_fn}({gt_fn}({va_name}, {vv_name}), all_ones)", prelude
            if op == "cmpge":
                return f"{xor_fn}({gt_fn}({vv_name}, {va_name}), all_ones)", prelude

    return None, ""


def _mask_bits_expr_for_reducer(type_name: str, ctx: FamilyBodyContext, mask_var: str) -> tuple[Optional[str], int]:
    if ctx.backend == "WASM":
        if type_name == "f32":
            return f"wasm_i32x4_bitmask((simd_i32){mask_var})", 1
        wasm_bitmask_fn = {
            "i8": "wasm_i8x16_bitmask",
            "i16": "wasm_i16x8_bitmask",
            "i32": "wasm_i32x4_bitmask",
            "i64": "wasm_i64x2_bitmask",
        }.get(type_name)
        if wasm_bitmask_fn:
            return f"{wasm_bitmask_fn}({mask_var})", 1
        return None, 1

    if ctx.backend == "AVX2":
        if type_name == "f32":
            return f"_mm256_movemask_ps({mask_var})", 1
        scale = {"i8": 1, "i16": 2, "i32": 4, "i64": 8}.get(type_name)
        if scale:
            return f"_mm256_movemask_epi8({mask_var})", scale
        return None, 1

    if ctx.backend == "SSE42":
        if type_name == "f32":
            return f"_mm_movemask_ps({mask_var})", 1
        scale = {"i8": 1, "i16": 2, "i32": 4, "i64": 8}.get(type_name)
        if scale:
            return f"_mm_movemask_epi8({mask_var})", scale
        return None, 1

    return None, 1


def _splat_scalar_value_fn(type_name: str, ctx: FamilyBodyContext) -> Optional[str]:
    if ctx.backend == "WASM":
        return ctx.backend_cfg.get("Set", {}).get("splat", {}).get(type_name)
    return ctx.backend_cfg.get("Set", {}).get("set1", {}).get(type_name)


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
    splat_fn = _splat_scalar_value_fn(type_name, _ctx)
    simd_cmp_expr, prelude = _compare_expr_scalar_reducer(op, type_name, _ctx, "va", "vv")
    bits_expr, scale = _mask_bits_expr_for_reducer(type_name, _ctx, "mask")
    if _ctx.load_func and splat_fn and simd_cmp_expr and bits_expr:
        ct_expr = "__builtin_popcount((u32)bits)"
        if scale != 1:
            ct_expr = f"(__builtin_popcount((u32)bits) / {scale})"
        prelude_block = f"{prelude}\n" if prelude else ""
        return f"""
static inline u64 stc_simd_count_{op}_scalar_{type_name}(const {type_name} * restrict a, const {type_name} value, const u64 len)
{{
    const u64 width = {_ctx.lanes};
    u64 i = 0;
    u64 ct = 0;
    const {_ctx.simd_type} vv = {splat_fn}(value);
{prelude_block}
    for (; (i + (2 * width)) <= len; i += (2 * width)) {{
        {_ctx.simd_type} va = {_ctx.load_func}((const {_ctx.simd_cast}*)(a + i));
        {_ctx.simd_type} mask = {simd_cmp_expr};
        u32 bits = (u32)({bits_expr});
        ct += (u64)({ct_expr});

        va = {_ctx.load_func}((const {_ctx.simd_cast}*)(a + i + width));
        mask = {simd_cmp_expr};
        bits = (u32)({bits_expr});
        ct += (u64)({ct_expr});
    }}

    for (; (i + width) <= len; i += width) {{
        {_ctx.simd_type} va = {_ctx.load_func}((const {_ctx.simd_cast}*)(a + i));
        {_ctx.simd_type} mask = {simd_cmp_expr};
        u32 bits = (u32)({bits_expr});
        ct += (u64)({ct_expr});
    }}

    for (; i < len; ++i) {{
        ct += (u64)({cmp_expr});
    }}

    return ct;
}}
""".strip()
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
    splat_fn = _splat_scalar_value_fn(type_name, _ctx)
    simd_cmp_expr, prelude = _compare_expr_scalar_reducer(op, type_name, _ctx, "va", "vv")
    bits_expr, scale = _mask_bits_expr_for_reducer(type_name, _ctx, "mask")
    if _ctx.load_func and splat_fn and simd_cmp_expr and bits_expr:
        lane_expr = "__builtin_ctz((u32)bits)"
        if scale != 1:
            lane_expr = f"(__builtin_ctz((u32)bits) / {scale})"
        prelude_block = f"{prelude}\n" if prelude else ""
        return f"""
static inline u64 stc_simd_first_{op}_scalar_{type_name}(const {type_name} * restrict a, const {type_name} value, const u64 len)
{{
    const u64 width = {_ctx.lanes};
    u64 i = 0;
    const {_ctx.simd_type} vv = {splat_fn}(value);
{prelude_block}
    for (; (i + (2 * width)) <= len; i += (2 * width)) {{
        {_ctx.simd_type} va = {_ctx.load_func}((const {_ctx.simd_cast}*)(a + i));
        {_ctx.simd_type} mask = {simd_cmp_expr};
        u32 bits = (u32)({bits_expr});
        if (bits) return i + (u64){lane_expr};

        va = {_ctx.load_func}((const {_ctx.simd_cast}*)(a + i + width));
        mask = {simd_cmp_expr};
        bits = (u32)({bits_expr});
        if (bits) return (i + width) + (u64){lane_expr};
    }}

    for (; (i + width) <= len; i += width) {{
        {_ctx.simd_type} va = {_ctx.load_func}((const {_ctx.simd_cast}*)(a + i));
        {_ctx.simd_type} mask = {simd_cmp_expr};
        u32 bits = (u32)({bits_expr});
        if (bits) return i + (u64){lane_expr};
    }}

    for (; i < len; ++i) {{
        if ({cmp_expr}) return i;
    }}
    return (u64)-1;
}}
""".strip()
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
        SimdFamilyRegistration(
            name="reduce",
            backends=all_backends,
            ops_per_type=ops_reduce_per_type,
            signature_emitter=emit_stc_template_function_signature_reduce,
            body_emitter=_emit_body_reduce,
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
