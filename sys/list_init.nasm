%include 'inc/func.inc'
%include 'inc/list.inc'

	fn_function sys/list_init
		;inputs
		;r0 = list head
		;trashes
		;r1

		lh_init r0, r1
		vp_ret

	fn_function_end