%ifndef CLASS_LISP_1234
%define CLASS_LISP_1234

%include 'class/class_ref.inc'

;%xdefine debug_lines

	def_class lisp, ref
	def_method create, class/lisp/create, static, {r0, r1, r2}, {r0}
	def_method new, class/lisp/new, static, {}, {r0}
	def_method init, class/lisp/init, static, {r0, r1, r2, r3, r5}, {r1}
	def_method error, class/lisp/error, static, {r0, r1, r2}
	def_method sym_intern, class/lisp/sym_intern, static, {r0, r1}, {r1}
	def_method sym_intern_cstr, class/lisp/sym_intern_cstr, static, {r0, r1}, {r1}
	def_method built_in_func, class/lisp/built_in_func, static, {r0, r1, r2}
	def_method env_set, class/lisp/env_set, static, {r0, r1, r2}
	def_method env_get, class/lisp/env_get, static, {r0, r1}, {r1}
	def_method env_find, class/lisp/env_find, static, {r0, r1}, {r1, r2}
	def_method env_set_list, class/lisp/env_set_list, static, {r0, r1, r2}, {r1}
	def_method env_push, class/lisp/env_push, static, {r0}
	def_method env_pop, class/lisp/env_pop, static, {r0}
	def_method repl, class/lisp/repl, static, {r0, r1}
	def_method repl_read, class/lisp/repl_read, static, {r0, r1, r2}, {r1, r2}
	def_method repl_read_list, class/lisp/repl_read_list, static, {r0, r1}, {r1}
	def_method repl_read_sym, class/lisp/repl_read_sym, static, {r0, r1, r2}, {r1, r2}
	def_method repl_read_num, class/lisp/repl_read_num, static, {r0, r1, r2}, {r1, r2}
	def_method repl_apply, class/lisp/repl_apply, static, {r0, r1}, {r1}
	def_method repl_eval, class/lisp/repl_eval, static, {r0, r1}, {r1}
	def_method repl_eval_list, class/lisp/repl_eval_list, static, {r0, r1}, {r1}
	def_method repl_print, class/lisp/repl_print, static, {r0, r1, r2}
	def_method func_def, class/lisp/func_def, static, {r0, r1}, {r1}
	def_method func_list, class/lisp/func_list, static, {r0, r1}, {r1}
	def_method func_lambda, class/lisp/func_lambda, static, {r0, r1}, {r1}
	def_method func_quote, class/lisp/func_quote, static, {r0, r1}, {r1}
	def_method func_add, class/lisp/func_add, static, {r0, r1}, {r1}
	def_method func_sub, class/lisp/func_sub, static, {r0, r1}, {r1}
	def_method func_mul, class/lisp/func_mul, static, {r0, r1}, {r1}
	def_method func_div, class/lisp/func_div, static, {r0, r1}, {r1}
	def_method func_mod, class/lisp/func_mod, static, {r0, r1}, {r1}
	def_method func_eq, class/lisp/func_eq, static, {r0, r1}, {r1}
	def_method func_cond, class/lisp/func_cond, static, {r0, r1}, {r1}
	def_method func_progn, class/lisp/func_progn, static, {r0, r1}, {r1}
	def_method func_not, class/lisp/func_not, static, {r0, r1}, {r1}
	def_method func_and, class/lisp/func_and, static, {r0, r1}, {r1}
	def_method func_or, class/lisp/func_or, static, {r0, r1}, {r1}

	def_method deinit, class/lisp/deinit, override

	def_structure lisp, ref
		ptr lisp_stdin
		ptr lisp_stdout
		ptr lisp_stderr
		ptr lisp_symbols
		ptr lisp_enviroment

		;same order as built_in_symbols table !
		ptr lisp_sym_parent
		ptr lisp_sym_nil
		ptr lisp_sym_t
		ptr lisp_sym_lambda
		ptr lisp_sym_def
		ptr lisp_sym_quote
		ptr lisp_sym_list
		ptr lisp_sym_add
		ptr lisp_sym_sub
		ptr lisp_sym_mul
		ptr lisp_sym_div
		ptr lisp_sym_mod
		ptr lisp_sym_eq
		ptr lisp_sym_cond
		ptr lisp_sym_progn
		ptr lisp_sym_not
		ptr lisp_sym_and
		ptr lisp_sym_or
	def_structure_end

%endif