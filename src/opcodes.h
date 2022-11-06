#ifdef OPCODE

OPCODE(LOAD_CONST)
OPCODE(LOAD_NAME)

OPCODE(IMPORT_NAME)
OPCODE(STORE_FAST)
OPCODE(STORE_NAME)

OPCODE(PRINT_EXPR)
OPCODE(POP_TOP)
OPCODE(CALL)
OPCODE(RETURN_VALUE)

OPCODE(BINARY_OP)
OPCODE(COMPARE_OP)
OPCODE(IS_OP)
OPCODE(CONTAINS_OP)

OPCODE(UNARY_NEGATIVE)
OPCODE(UNARY_NOT)

OPCODE(DUP_TOP)

OPCODE(BUILD_LIST)
OPCODE(BUILD_TUPLE)
OPCODE(BUILD_MAP)
OPCODE(BUILD_SLICE)
OPCODE(UNPACK_SEQUENCE)

OPCODE(BINARY_SUBSCR)
OPCODE(STORE_SUBSCR)
OPCODE(DELETE_SUBSCR)

OPCODE(LOAD_ATTR)
OPCODE(STORE_ATTR)

OPCODE(GET_ITER)
OPCODE(FOR_ITER)

OPCODE(POP_JUMP_IF_FALSE)
OPCODE(JUMP_ABSOLUTE)
OPCODE(JUMP_IF_TRUE_OR_POP)
OPCODE(JUMP_IF_FALSE_OR_POP)

// non-standard python opcodes
OPCODE(LOAD_NONE)
OPCODE(LOAD_TRUE)
OPCODE(LOAD_FALSE)

OPCODE(ASSERT)
OPCODE(RAISE_ERROR)

OPCODE(STORE_FUNCTION)
OPCODE(BUILD_CLASS)

#endif