%include 'inc/func.inc'
%include 'inc/string.inc'
%include 'cmd/cmd.inc'

	fn_function cmd/cmd_stdout
		;inputs
		;r0 = pipe
		;r1 = buffer
		;r2 = length
		;trashes
		;all but r4

		ptr pipe
		ptr buffer
		ulong length
		ptr msg

		push_scope
		retire {r0, r1, r2}, {pipe, buffer, length}
		static_call sys_mail, alloc, {}, {msg}
		assign {cmd_mail_stream_size + length}, {msg->ml_msg_length}
		assign {pipe->cmd_pipe_stdout_id.mb_mbox}, {msg->ml_msg_dest.mb_mbox}
		assign {pipe->cmd_pipe_stdout_id.mb_cpu}, {msg->ml_msg_dest.mb_cpu}
		static_call sys_mem, copy, {buffer, &msg->cmd_mail_stream_string, length}, {_, _}
		assign {pipe->cmd_pipe_stdout_seqnum}, {msg->cmd_mail_stream_seqnum}
		assign {pipe->cmd_pipe_stdout_seqnum + 1}, {pipe->cmd_pipe_stdout_seqnum}
		static_call sys_mail, send, {msg}
		pop_scope
		vp_ret

	fn_function_end