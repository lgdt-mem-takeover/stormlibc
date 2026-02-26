#include <stdio.h>
#include <string.h>

#define TOK_LITERAL(lexer, token) (struct stc_string8){.str = lexer->src.str + token.start, .len = token.end - token.start}
#define STRING_SIZED(string) (int)string.len, string.str
#define PRINT_STRING(string) printf("%.*s\n", (int)string.len, string.str)
#define ARR_SIZE(arr) sizeof(arr) / sizeof(arr[0])

#define IDXOF(i, arr) (i - arr)

#define LOOP(arr, len, capture) \
	capture = arr;		\
	for (__typeof__(arr[0]) *end = arr + len; capture != end; ++capture)

enum tok_type {
	TOK_INVALID = 128,
	TOK_CENUM,
	TOK_CSTRUCT,
	TOK_STRING_TABLE,
	TOK_IDENT,
	TOK_STRING,
	TOK_INTEGER,
	TOK_FLOAT,
	TOK_LET,
	CT_TOK_TYPES
};

struct token {
	enum tok_type	type;
	u32		start;
	u32		end;
};

struct lexer {
	struct stc_string8	src;
	struct token		*tokens;
	u64			ct_tokens;
	u64			cur;
	u64			start;
};

thisfile char *strp_xt(char *s)
{
	if (s == NULL) return NULL;

	u64 len = sstrlenx(s);
	if (len == 0) return NULL;
	i64 end = len - 1;
	bool has_xt = false;
	char *out = stc_os_alloc_default(len);
	strcpy(out, s);

	while (end > 0) {
		if (out[end] == '.') {
			has_xt = true;
			break;
		}
		end--;
	}

	if (!has_xt) return NULL;

	out[end] = '\0';
	return out;
}

thisfile inline bool is_wspace(char ch)
{
	return (ch == ' ') || (ch == '\r') || (ch == '\t') || (ch == '\v') || (ch == '\f') || (ch == '\n');
}


thisfile inline bool is_ascii(char ch)
{
	return ch <= 127;
}



thisfile char eat(struct lexer *l)
{
	if (l->cur >= l->src.len) {
		printf("[FUNC %s]Tried out of bounds access. Exiting\n", __func__);
		exit(1);
	}
	char ch = l->src.str[l->cur++];
	return ch;
}

thisfile char top(struct lexer *l)
{
	return l->src.str[l->cur];
}


thisfile bool match(struct lexer *l, char ch) {
	bool is_match = top(l) == ch;
	u64 next_if_match = l->cur + 1;
	l->cur = SELECT(is_match, next_if_match, l->cur);
	return is_match;
}


thisfile void add_token(struct lexer *l, enum tok_type type)
{
	l->tokens[l->ct_tokens].type	= type;
	l->tokens[l->ct_tokens].start	= l->start;
	l->tokens[l->ct_tokens].end	= l->cur;
	l->ct_tokens++;
}


thisfile void tokenize(struct lexer *l)
{
	struct stc_string8 let_literal = STR("let");
	struct stc_string8 temp_string = {0};
	temp_string.str = stc_os_alloc_default(4096);
	char *iter;
MAIN:
	if (l->cur >= l->src.len) goto FINISH;
	l->start = l->cur;
	char ch = eat(l);


	if (is_wspace(ch)) goto MAIN;
	else if (ch == '@') goto PARSE_BUILTIN;
	else if (ch == '"') goto PARSE_STRING;
	else if (is_alpha(ch)) goto PARSE_IDENT;
	else if (is_char_digit(ch)) goto PARSE_DIGIT;
	else if (is_ascii(ch)) {add_token(l, ch);}
	else {
		printf("Invalid character %c\n", ch);
		exit(1);
	}
goto MAIN;



PARSE_DIGIT:
	if (top(l) == '.') {
		eat(l);
		while (is_char_digit(top(l))) {
			eat(l);
		}
		add_token(l, TOK_FLOAT);
		goto MAIN;
	}
	while (is_char_digit(top(l))) {
		eat(l);
	}
	add_token(l, TOK_INTEGER);
	goto MAIN;



PARSE_IDENT:
	while (is_alnum(top(l)) || top(l) == '_') {
		eat(l);
	}

	temp_string.str = l->src.str + l->start;
	temp_string.len = l->cur - l->start;
	if (sstrcmpx(temp_string, let_literal)) {
		add_token(l, TOK_LET);
		goto MAIN;
	}
	add_token(l, TOK_IDENT);
	goto MAIN;

PARSE_STRING: {
	while(top(l) != '"') {
		eat(l);
	}
	eat(l);
	add_token(l, TOK_STRING);
	goto MAIN;

}

PARSE_BUILTIN: {
	struct stc_string8 at_string_table = STR("@string_table");
	struct stc_string8 at_cenum = STR("@cenum");
	struct stc_string8 at_cstruct = STR("@cstruct");
	if (!is_alpha(top(l))) {
		fprintf(stderr, "Unknown symbol \"%c\" after \"@\" declaration", top(l));
		exit(1);
	}

	while (is_alpha(top(l)) || top(l) == '_') {
		eat(l);
	}

	struct stc_string8 strng = (struct stc_string8){.str = l->src.str + l->start, .len = l->cur - l->start};

	if (sstrcmpx(at_string_table, strng))  {
		add_token(l, TOK_STRING_TABLE);
	} else if (sstrcmpx(at_cenum, strng)) {
		add_token(l, TOK_CENUM);
	} else if (sstrcmpx(at_cstruct, strng)) {
		add_token(l, TOK_CSTRUCT);

	}
	goto MAIN;
}


FINISH:
	return;
}


struct label_entry {
	struct token	enum_label;
	struct token	enum_pair;
};

struct string_table {
	struct token		table_name;
	struct token		enum_type;
	struct label_entry	*label_entry;
	u64			ct_labels;
	u64			fmt_pair;
	u64			max_labels;
};



struct let_stmt {
	struct token	ident_name;
	struct token	*assignees;
	u32		ct_assignees;
};

enum codegen_type {
	TYPE_STRING_TABLE,
	TYPE_LET_STMT,
	CT_CODEGEN_TYPE
};


struct cenum{
	struct token	enum_lbl;
	struct token	elems[1024];
	u64		ct_elems;
};

struct codegen_data {
	struct string_table	*str_tbl;
	u64			 ct_str_tbl;
	struct let_stmt		*let_stmts;
	u64			ct_let_stmts;
	struct cenum		*cenums;
	u64			ct_cenums;
};



thisfile inline u64 str_table_label_push(struct string_table * restrict t, struct label_entry entry)
{
	t->label_entry[t->ct_labels++] = entry;
	return t->ct_labels - 1;
}



thisfile struct token tok_eat(struct lexer *l)
{
	if (l->cur >= l->ct_tokens) {
		printf("[FUNC %s]Tried out of bounds access. Exiting\n", __func__);
		exit(1);
	}

	struct token tok = l->tokens[l->cur++];
	return tok;
}

thisfile struct token tok_top(struct lexer *l)
{
	return l->tokens[l->cur];
}

thisfile struct token tok_prev(struct lexer *l)
{
	return l->tokens[l->cur - 1];
}


thisfile bool tok_match(struct lexer *l, enum tok_type type) {
	bool is_match = tok_top(l).type == type;
	u64 next_if_match = l->cur + 1;
	l->cur = SELECT(is_match, next_if_match, l->cur);
	return is_match;
}


#define PARAM_TYPES \
	X(INVALID_PARAM),\
	X(LC),\
	X(UC),\
	X(CP),

enum fmt_pair {
	#define X(name) name
	PARAM_TYPES
	CT_PARAM_TYPES
	#undef X
};

thisfile struct stc_string8 fmt_pair_lit[] = {
	#define X(name) [name] = STR(#name)
	PARAM_TYPES
	#undef X
};



thisfile void add_ast_node(struct codegen_data * restrict c, struct lexer * restrict l, enum codegen_type type, void *node)
{
	switch (type) {
	case TYPE_STRING_TABLE:
		break;
	case TYPE_LET_STMT:
		c->let_stmts[c->ct_let_stmts++] = *(struct let_stmt*)node;
		break;
	default: unreachable;
	}
}


thisfile void build_data(struct codegen_data * restrict c, struct lexer * restrict l)
{
	l->start = l->cur = 0;
	struct token tok_cur;
	struct stc_string8 tok_cur_lit;
	struct let_stmt cur_letstmt = {};
	struct stc_stack *stack_letstmts = stc_stack_gen(1lu << 31);
	cur_letstmt.assignees = stc_stack_push(stack_letstmts, struct token, 1024);

	goto ADVANCE;

LOOP:
	switch (tok_cur.type) {
	case TOK_INVALID:
		printf("Invalid token. Exiting\n");
		exit(1);
	case TOK_STRING_TABLE: goto BUILD_STRING_TABLE;
	case TOK_CENUM: goto BUILD_CENUM;
	case TOK_CSTRUCT: goto BUILD_CSTRUCT;
	case TOK_LET: goto PARSE_LET_STMT;
	default:
		printf("Ignoring unexpected token %.*s\n", STRING_SIZED(TOK_LITERAL(l, tok_prev(l))));
		break;
	}



ADVANCE:
	if (l->cur >= l->ct_tokens) goto FINISH;
	tok_cur = tok_eat(l);
	tok_cur_lit = TOK_LITERAL(l, tok_cur);
	goto LOOP;




BUILD_CENUM:
	tok_cur = tok_eat(l);
	c->cenums[c->ct_cenums].enum_lbl = tok_cur;
	if (!tok_match(l, '{')) {
		printf("Missing '{' at the start of '@cenum' declaration");
		exit(1);
	}


	while (tok_top(l).type != '}') {
		u64 *ct_elems = &c->cenums[c->ct_cenums].ct_elems;
		c->cenums[c->ct_cenums].elems[*ct_elems] = tok_top(l);
		(*ct_elems)++;
		tok_cur = tok_eat(l);
	}

	if (!tok_match(l, '}')) {
		printf("Missing '}' at the end of '@cenum' declaration");
		exit(1);
	}
	if (!tok_match(l, ';')) {
		printf("Missing ';' at the end of block");
		exit(1);
	}
	c->ct_cenums++;
	printf("ct cenums: %lu\n", c->ct_cenums);
	goto ADVANCE;

BUILD_CSTRUCT:
	goto ADVANCE;

PARSE_LET_STMT:
	cur_letstmt.assignees = stc_stack_push(stack_letstmts, struct token, 1024);
	cur_letstmt.ct_assignees = 0;
	if (!tok_match(l, TOK_IDENT)) {
		printf("Missing identifier after token 'let'\n");
		exit(1);
	}

	cur_letstmt.ident_name = tok_prev(l);

	if (!tok_match(l, '=')) {
		printf("Missing '=' after identifier\n");
		exit(1);
	}

	while (tok_top(l).type != ';') {
		if (tok_match(l, TOK_IDENT)) {
			cur_letstmt.assignees[cur_letstmt.ct_assignees++] = (struct token){.type = TOK_IDENT, .start = tok_prev(l).start, .end = tok_prev(l).end};
		} else if (tok_match(l, '-')) {
			cur_letstmt.assignees[cur_letstmt.ct_assignees++] = (struct token){.type = '-', .start = tok_prev(l).start, .end = tok_prev(l).end};
		} else if (tok_match(l, '*')) {
			cur_letstmt.assignees[cur_letstmt.ct_assignees++] = (struct token){.type = '*', .start = tok_prev(l).start, .end = tok_prev(l).end};
		} else if (tok_match(l, '/')) {
			cur_letstmt.assignees[cur_letstmt.ct_assignees++] = (struct token){.type = '/', .start = tok_prev(l).start, .end = tok_prev(l).end};
		} else if (tok_match(l, '%')) {
			cur_letstmt.assignees[cur_letstmt.ct_assignees++] = (struct token){.type = '%', .start = tok_prev(l).start, .end = tok_prev(l).end};
		} else if (tok_match(l, '+')) {
			cur_letstmt.assignees[cur_letstmt.ct_assignees++] = (struct token){.type = '+', .start = tok_prev(l).start, .end = tok_prev(l).end};
		} else if (tok_match(l, TOK_INTEGER)) {
			cur_letstmt.assignees[cur_letstmt.ct_assignees++] = (struct token){.type = TOK_INTEGER, .start = tok_prev(l).start, .end = tok_prev(l).end};
		} else if (tok_match(l, TOK_FLOAT)) {
			cur_letstmt.assignees[cur_letstmt.ct_assignees++] = (struct token){.type = TOK_FLOAT, .start = tok_prev(l).start, .end = tok_prev(l).end};
		} else if (tok_match(l, '(')) {
			cur_letstmt.assignees[cur_letstmt.ct_assignees++] = (struct token){.type = '(', .start = tok_prev(l).start, .end = tok_prev(l).end};
		} else if (tok_match(l, ')')) {
			cur_letstmt.assignees[cur_letstmt.ct_assignees++] = (struct token){.type = ')', .start = tok_prev(l).start, .end = tok_prev(l).end};
		} else {
			printf("Unexpected token %.*s\n", STRING_SIZED(TOK_LITERAL(l, tok_top(l))));
			exit(1);
		}

	}
	if (!tok_match(l, ';')) {
		printf("Missing ';' at the end of declaration statement");
		exit(1);
	}
	add_ast_node(c, l, TYPE_LET_STMT, &cur_letstmt);

	goto ADVANCE;

BUILD_STRING_TABLE:
	if (!tok_match(l, TOK_IDENT)) {
		printf("Expected identifier for string table. Found: ");
		PRINT_STRING(tok_cur_lit);
		exit(1);
	}
	c->str_tbl[c->ct_str_tbl].table_name = tok_prev(l);

	if (!tok_match(l, '(')) {
		printf("Expected '('\n");
		exit(1);
	}

	while (tok_top(l).type != ')') {
		if (tok_match(l, ',')){
			continue;
		}
		else if (tok_match(l, TOK_IDENT)) {
			tok_cur_lit = TOK_LITERAL(l, tok_prev(l));
			bool matched = false;
			for (u64 i = 0; i < CT_PARAM_TYPES; ++i) {
				if (sstrcmpx(tok_cur_lit, fmt_pair_lit[i])) {
					c->str_tbl[c->ct_str_tbl].fmt_pair = i;
					// PRINT_STRING(fmt_pair_lit[i]);
					matched = true;
				}
			}
			if (!matched) {
				printf("Could not match paramter: ");
				PRINT_STRING(tok_cur_lit);
				exit(1);
			}

		} else {
			printf("Unexepected token: ");
			PRINT_STRING(TOK_LITERAL(l, tok_top(l)));

		}
	}
	if (!tok_match(l, ')')) {
		printf("Expected closing paren ')'");
		exit(1);
	}

	if (!tok_match(l, ':')) {
		printf("Expected ':' before string table enum type\n");
		exit(1);
	}

	if (!tok_match(l, TOK_IDENT)) {
		printf("Expected enum type after ':'\n");
		exit(1);
	}

	c->str_tbl[c->ct_str_tbl].enum_type = tok_prev(l);

	if (!tok_match(l, '{')) {
		printf("Expected opening bracket '{'");
		exit(1);
	}


	while (tok_top(l).type != ';') {
		if (!tok_match(l, '{')) {
			printf("Entry label must start with opening curly bracket '{'");
			exit(1);
		}
		while (tok_top(l).type != '}') {
			if (tok_match(l, TOK_IDENT)) {
				struct label_entry entry = {0};
				entry.enum_label = tok_prev(l);
				entry.enum_pair = tok_top(l);
				if (!tok_match(l, TOK_STRING)) {
					printf("Expected string pair for: %.*s\nFound %.*s\n", STRING_SIZED(TOK_LITERAL(l, entry.enum_label)), STRING_SIZED(TOK_LITERAL(l, entry.enum_pair)));
					exit(1);
				}
				str_table_label_push(&c->str_tbl[c->ct_str_tbl], entry);
			} else {
				printf("Unknown token type: ");
				PRINT_STRING(TOK_LITERAL(l, tok_top(l)));
				exit(1);
			}
		}
		if (!tok_match(l, '}')) {
			printf("Expected closing bracket '}' at the end of label entry");
			exit(1);
		}
		if (tok_match(l, '}')) {
			break;
		}
	}
	if (!tok_match(l, ';')) {
		printf("Expected semicol at the end of block ';'");
		exit(1);
	}

	c->ct_str_tbl++;
	goto ADVANCE;




FINISH:
	return;
}





thisfile struct stc_string8 format_string(struct stc_stack *s, struct stc_string8 *target, enum fmt_pair fmt_type)
{
	struct stc_string8 pl = {};
	pl.str = stc_stack_push(s, char, target->len);
	sstrcpyx(&pl, target);

	u64 i = 0;
	char *ch;
	bool is_lower = false;
	bool is_upper = false;
	char if_lower = 0;
	char if_upper = 0;
	switch (fmt_type) {
	case CP:
		while(!is_alpha(pl.str[i])) {
			++i;
		}
		is_lower = is_lowercase(pl.str[i]);
		if_lower = pl.str[i] - 32;
		pl.str[i] = SELECT(is_lower, if_lower, pl.str[i]);
		LOOP((pl.str + i + 1), pl.len, ch) {
			is_upper = is_uppercase((*ch));
			if_upper = *ch + 32;
			(*ch) = SELECT(is_upper, if_upper, (*ch));
		}
		break;
	case UC:
		LOOP(pl.str, pl.len, ch) {
			is_lower = is_lowercase((*ch));
			if_lower = *ch - 32;
			(*ch) = SELECT(is_lower, if_lower, (*ch));
		}
		break;
	case LC:
		LOOP(pl.str, pl.len, ch) {
			is_upper = is_uppercase((*ch));
			if_upper = *ch + 32;
			(*ch) = SELECT(is_upper, if_upper, (*ch));
		}
		break;
	default: break;
	}

	return pl;

}



struct unique_enums{
	struct token	enum_type_name;
	struct token	enum_label[1024];
	u64		ct_labels;
};


thisfile bool enum_exists_in_set(struct unique_enums * restrict u, u64 ct_enums, struct lexer * restrict l, struct token t)
{
	struct unique_enums *val_unqe;
	LOOP(u, ct_enums, val_unqe) {
		struct stc_string8 cur_unqe = TOK_LITERAL(l, t);
		if (sstrcmpx(cur_unqe, TOK_LITERAL(l, (*val_unqe).enum_type_name))) {
			return true;
		}
	}

	return false;
}


thisfile u64 code_gen(struct stc_stack * restrict s, struct codegen_data * restrict c, struct lexer * restrict l, const char * restrict path)
{
	int err_check = 0;
	const u64 buffer_size = 1<<14;
	u64 total_added = 0;
	struct string_table *val_tbl;
	char *out_buffer = stc_stack_push(s, char, buffer_size);
	int buffer_offset = 0;
	buffer_offset += snprintf(out_buffer + buffer_offset, buffer_size - buffer_offset, "#include \"/usr/include/storm/core/stormc_types.h\"\n\n\n\n");


	struct unique_enums *uniq_enums = stc_stack_push(s, struct unique_enums, c->ct_str_tbl);
	u64 ct_uniq_enums = 0;
	struct cenum *val_cenum;
	LOOP(c->str_tbl, c->ct_str_tbl, val_tbl) {
		struct token tok_cur_enum_type = (*val_tbl).enum_type;
		if (!enum_exists_in_set(uniq_enums, c->ct_str_tbl ,l, tok_cur_enum_type)) {
			uniq_enums[ct_uniq_enums].enum_type_name = tok_cur_enum_type;
			u64 *ct_labels = &uniq_enums[ct_uniq_enums].ct_labels;
			for (u64 idx = 0; idx < (val_tbl)->ct_labels; ++idx) {
				struct token e_lbl = (*val_tbl).label_entry[idx].enum_label;
				uniq_enums[ct_uniq_enums].enum_label[*ct_labels] = e_lbl;
				(*ct_labels)++;
			}
			ct_uniq_enums++;
		}
	}
	for (u64 idx = 0; idx < ct_uniq_enums; ++idx) {
		buffer_offset += snprintf(
			out_buffer + buffer_offset,
			buffer_size - buffer_offset,
			"enum %.*s{\n", STRING_SIZED(TOK_LITERAL(l, uniq_enums[idx].enum_type_name)));
		for (u64 jdx = 0; jdx < uniq_enums[idx].ct_labels; ++jdx) {
			buffer_offset += snprintf(
				out_buffer + buffer_offset, buffer_size - buffer_offset,
				"\t%.*s,\n", STRING_SIZED(format_string(s, &TOK_LITERAL(l, uniq_enums[idx].enum_label[jdx]), UC))

			);
		}
		buffer_offset += snprintf(
			out_buffer + buffer_offset,
			buffer_size - buffer_offset,
			"\tCT_%.*s\n", STRING_SIZED(format_string(s, &TOK_LITERAL(l, uniq_enums[idx].enum_type_name), UC)));
		buffer_offset += snprintf(out_buffer + buffer_offset, buffer_size - buffer_offset, "};\n\n");
	}

	out_buffer[buffer_offset] = '\0';
	// printf("%s\n", out_buffer);

	LOOP(c->str_tbl, c->ct_str_tbl, val_tbl) {
		struct label_entry *v_entry;
		struct stc_string8 tbl_name = TOK_LITERAL(l, val_tbl->table_name);
		struct stc_string8 uppercase_enum_decl = format_string(s, &tbl_name, UC);

		buffer_offset += snprintf(
			out_buffer + buffer_offset, buffer_size - buffer_offset,
			"thisfile struct stc_string8  table_%.*s[] = {\n",
			STRING_SIZED(tbl_name)
			);


		LOOP(val_tbl->label_entry, val_tbl->ct_labels, v_entry) {
			struct stc_string8 uppercase_enum = format_string(s, &TOK_LITERAL(l, v_entry->enum_label), UC);
			struct stc_string8 capitalised_pair = format_string(s, &TOK_LITERAL(l, v_entry->enum_pair), val_tbl->fmt_pair);
			buffer_offset += snprintf(
				out_buffer + buffer_offset, buffer_size - buffer_offset,
				"\t[%.*s] = STR(%.*s),\n",
				STRING_SIZED(uppercase_enum),
				STRING_SIZED(capitalised_pair)
				);
		}
		buffer_offset += snprintf(
			out_buffer + buffer_offset, buffer_size - buffer_offset,
			"};\n\n");
		total_added++;

	}


	// printf("%.*s\n", buffer_offset, out_buffer);

	char path_buff[1024];
	u64 off_path_buff = 0;
	off_path_buff = snprintf(path_buff + off_path_buff, sizeof(path_buff) - off_path_buff,
		"%s.h", strp_xt(path));
	FILE *f = fopen(path_buff, "w+");
	if (!f) {
		perror("fopen");
	}
	err_check = fwrite(out_buffer, 1, buffer_offset, f);
	if (err_check != buffer_offset) {
		perror("fwrite");
		exit(1);
	}
	err_check = fclose(f);
	if (err_check != 0) {
		perror("fclose");
		exit(1);
	}
	return total_added;
}



#define MAX_ARGS 16
struct eval_frame {
	char	op;
	i64	args[MAX_ARGS];
	u32	ct_args;
};

#define MAX_FRAMES 128
struct eval_stack {
	struct eval_frame	frames[MAX_FRAMES];
	u32			ct_frames;
};

thisfile u64 parse_expr(struct codegen_data * restrict c, struct lexer * restrict l)
{

}

thisfile u64 resolve_value(struct codegen_data * restrict c, struct lexer * restrict l, struct let_stmt stmt)
{
	struct eval_stack stack = {0};
	struct token cur = {0};
	struct eval_frame *f;
	u64 i = 0;
	i64 total = 0;
	i64 result = 0;
LOOP:
	if (i >= stmt.ct_assignees) goto FINISH;
		cur = stmt.assignees[i];

		if (cur.type == '*' || cur.type == '/' || cur.type == '+' || cur.type == '-') {
			// PRINT_STRING(TOK_LITERAL(l, cur));
			stack.frames[stack.ct_frames].op = cur.type;
			stack.ct_frames++;
			goto ADVANCE;

		}
		if (cur.type == TOK_FLOAT || cur.type == TOK_INTEGER || cur.type == TOK_IDENT) {
			// PRINT_STRING(TOK_LITERAL(l, cur));
			stack.frames[stack.ct_frames - 1].args[stack.frames[stack.ct_frames - 1].ct_args++] = satoix(TOK_LITERAL(l, cur).str);
			goto ADVANCE;
		}
		if (cur.type == '(')  goto ADVANCE;
		if (cur.type == ')')  goto EVAL;


ADVANCE:
	++i;
	goto LOOP;

EVAL:
	f = &stack.frames[stack.ct_frames - 1];
	result = 0;

	switch (f->op) {
	case '+':
		for (u32 j = 0; j < f->ct_args; ++j) {
			result += f->args[j];
		}
		break;

	case '*':
		result = 1;
		for (u32 j = 0; j < f->ct_args; ++j) {
			result *= f->args[j];
		}
		break;

	case '-':
		result = f->args[0];
		for (u32 j = 1; j < f->ct_args; ++j) {
			result -= f->args[j];
		}
		break;

	case '/':
		result = f->args[0];
		for (u32 j = 1; j < f->ct_args; ++j) {
			if (f->args[j] == 0) {
				printf("Cannot divide by zero\n");
				exit(1);
			}
			result /= f->args[j];
		}
		break;

	}

	stack.ct_frames--;

	if (stack.ct_frames > 0) {
		struct eval_frame *parent = &stack.frames[stack.ct_frames - 1];
		parent->args[parent->ct_args++] = result;
	} else {
		total = result;
	}

	++i;
	goto LOOP;


FINISH:
	return total;
}


int exec_codegen(char *path)
{
	struct stc_stack *s = stc_stack_gen(1lu << 38);
	struct lexer *l = stc_stack_push(s, struct lexer, 1);
	struct codegen_data *c = stc_stack_push(s, struct codegen_data, 1);
	c->str_tbl = stc_stack_push(s, struct string_table, 1024);
	c->let_stmts = stc_stack_push(s, struct let_stmt, 1000000);
	c->cenums = stc_stack_push(s, struct cenum, 1024);

	FILE *f = fopen(path, "r");
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, 0, SEEK_SET);
	l->src.str = stc_stack_push(s, struct stc_string8, size + 1);
	l->tokens = stc_stack_push(s, struct token, size + 1);
	if (!f) {
		perror("fopen");
		exit(1);
	}
	l->src.len = fread(l->src.str, 1, size, f);
	l->src.str[l->src.len] = '\0';

	for (u64 i = 0; i < 1024; ++i) {
		c->str_tbl[i].label_entry = stc_stack_push(s, struct label_entry, 1024);
		c->str_tbl[i].max_labels = 1024;
	}


	tokenize(l);
	build_data(c, l);

	u64 ret_count = code_gen(s, c, l, path);
	if (ret_count != c->ct_str_tbl) {
		printf("Mismatch table add\n");
	}

	for (u64 i = 0; i < c->ct_let_stmts; ++i) {
		resolve_value(c, l, c->let_stmts[i]);
	}


	int err_check = fclose(f);
	if (err_check != 0) {
		perror("fclose");
		exit(1);
	}


	return 0;
}
