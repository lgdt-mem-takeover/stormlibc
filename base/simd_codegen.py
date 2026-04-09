from dataclasses import dataclass
from typing  import List

stc_enum_count = 0;

def next_id():
    global stc_enum_count
    v = stc_enum_count
    stc_enum_count += 1
    return v


LOAD = next_id();
STORE = next_id();
SET1 = next_id();
ADD = next_id();
SUB = next_id();
MUL = next_id();
DIV = next_id();
SELECT = next_id();
HSUM = next_id();
HSUB = next_id();

stc_ops_enums = [LOAD, STORE, SET1, ADD, SUB, MUL, DIV, SELECT, HSUM, HSUB];


@dataclass
class IMPL_WASM:
    intrin_names: List[str]
    pass


@dataclass
class IMPL_AVX2:
    intrin_names: List[str]
    pass

@dataclass
class IMPL_SSE42:
    intrin_names: List[str]
    pass

stc_enum_count = 0


ops = [
    "load", "store", "set1", "add", "sub", "mul", "div",
    "select", "hadd", "hsub"
];
stc_simd_params_1 = "{typea} a"
stc_simd_params_2 = "{typea} *restrict a, {typeb} *restrict b"
stc_simd_params_3 = "{typea} *restrict a, {typeb} *restrict b, {typec} c"
stc_types = ["u8", "u16", "u32", "u64", "i8", "i16", "i32", "i64", "f32", "f64"];


x86_suffix = {
    "u8": "epi8",
    "u16": "epi16",
    "u32": "epi32",
    "u64": "epi64",
    "i8": "epi8",
    "i16": "epi16",
    "i32": "epi32",
    "i64": "epi64",
    "f32": "ps",
    "f64": "pd",
}

wasm_suffix = [
    "wasm_v128_load",
    "wasm_v128_store",
    "wasm_v128_splat",
    "wasm_v128_add",
    "wasm_v128_sub",
    "wasm_v128_mul",
    "wasm_v128_div",
    "wasm_v128_bitselect",
    "custom",
]

avx2_suffix = [
    "_mm256_loadu_*",
    "_mm256_storeu_*",
    "_mm256_set1_*",
    "_mm256_add_*",
    "_mm256_sub_*",
    "_mm256_mul_*",
    "_mm256_div_*",
    "_mm256_blendv_*",
    "custom",
]

sse42_suffix = [
    "_mm_loadu_*",
    "_mm_storeu_*",
    "_mm_set1_*",
    "_mm_add_*",
    "_mm_sub_*",
    "_mm_mul_*",
    "_mm_div_*",
    "custom",
    "custom",
]

ops_mappings = {
    LOAD: {
        "params": "{const typea a}",
        "return": "",
        "signature": "",
    },
    STORE: {
        "params": "{typea} a simd_{typeb} *v",
        "return": "void",
        "signature": "",
    },
    SET1: {
        "params": stc_simd_params_1,
        "return": "void",
        "signature": "",
    },
    ADD: {
        "params": stc_simd_params_2,
        "return": "void",
        "signature": "",
    },
    SUB: {
        "params": stc_simd_params_2,
        "return": "void",
        "signature": "",
    },
    MUL:{
        "params": stc_simd_params_2,
        "return": "void",
        "signature": "",
    },
    DIV: {
        "params": stc_simd_params_2,
        "return": "void",
        "signature": "",
    },
    SELECT: {
        "params": stc_simd_params_2,
        "return": "void",
        "signature": "",
    },
    HSUM: {
        "params": stc_simd_params_2,
        "return": "void",
        "signature": "",
    },
    HSUB: {
        "params": stc_simd_params_2,
        "return": "void",
        "signature": "",
    },
};



for t in stc_types:
    for i in range(len(ops)):
        print(f"{ops_mappings[i]["return"].format(typer = t)} stc_simd_{t}_{ops[i]}({ops_mappings[i]["params"].format(typea = t, typeb = t)});");


