(import 'sys/code.inc)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; system call register saves
; and sys-call macro
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(cond
	((eql *os* 'Darwin)
		(defcfun sys-call (_) (vp-syscall (add _ 0x2000000)))
		(cond
			((eql *cpu* 'x86_64)
				(defmacro sys-args (_ &optional o) (setd o 0) `',(slice o (add o _) '(r6 r5 r2 r9 r7 r8)))
				(defmacro sys-trashed () ''(r1 r2 r5 r6 r7 r8 r9 r10)))
			(t (throw "Unknown CPU for Darwin !" *cpu*))))
	((eql *os* 'Linux)
		(defcfun sys-call (_) (vp-syscall _))
		(cond
			((eql *cpu* 'x86_64)
				(defmacro sys-args (_ &optional o) (setd o 0) `',(slice o (add o _) '(r6 r5 r2 r9 r7 r8)))
				(defmacro sys-trashed () ''(r1 r2 r5 r6 r7 r8 r9 r10)))
			((eql *cpu* 'aarch64)
				(defmacro sys-args (_ &optional o) (setd o 0) `',(slice o (add o _) '(r0 r1 r2 r3 r4 r5)))
				(defmacro sys-trashed () ''(r1 r2 r3 r4 r5 r6 r7 r8 r9 r10 r11 r12 r13 r14)))
			(t (throw "Unknown CPU for Linux !" *cpu*)))))

(defcmacro sys-push-trashed (&rest b) (merge-sym b (sys-trashed)) `(vp-push ~b))
(defcmacro sys-pop-trashed (&rest b) (merge-sym b (sys-trashed)) `(vp-pop ~b))
(defcmacro sys-arg (_) (elem _ (sys-args 6)))

;;;;;;;;;;;;;;;;
; syscall macros
;;;;;;;;;;;;;;;;

(when (eql *os* 'Darwin)
	(defcfun sys-gettimeofday (_)
		;time, timezone
		(assign _ (sys-args 2))
		(vp-push (sys-arg 0))
		(vp-xor-rr (sys-arg 2) (sys-arg 2))
		(sys-call sys_gettimeofday)
		(vp-pop (sys-arg 1))
		(vpif '(r0 != 0))
			(vp-cpy-ri r0 (sys-arg 1) timeval_sec)
			(vp-cpy-ri (sys-arg 2) (sys-arg 1) timeval_usec)
		(endif)))

(when (eql *os* 'Linux)
	(defcfun sys-gettimeofday (_)
		;time, timezone
		(assign _ (sys-args 2))
		(sys-call sys_gettimeofday)))

(def-struct 'timeval)
	(long 'sec)
	(long 'usec)
(def-struct-end)

(def-struct 'timezone)
	(int 'minuteswest)
	(int 'dsttime)
(def-struct-end)

(defcfun sys-open (_1 _2)
	;path, flags, mode
	(assign (cat '(at_fdcwd) _1) (sys-args 4))
	(sys-call sys_openat)
	(assign '(r0) _2))

(defcfun sys-unlink (_1 _2)
	;name
	(assign (cat '(at_fdcwd) _1 '(0)) (sys-args 3))
	(sys-call sys_unlinkat)
	(assign '(r0) _2))

(defcfun sys-stat (_1 _2)
	;path, buffer
	(assign (cat '(at_fdcwd) _1 '(0)) (sys-args 4))
	(sys-call sys_fstatat)
	(assign '(r0) _2))

(defcfun sys-exit (_)
	;return code
	(assign _ (sys-args 1))
	(sys-call sys_exit))

(defcfun sys-read (_1 _2)
	;fd, buffer, length
	(assign _1 (sys-args 3))
	(sys-call sys_read)
	(assign '(r0) _2))

(defcfun sys-read-char (_1 _2)
	;fd
	(assign _1 (sys-args 1))
	(vp-xor-rr (sys-arg 1) (sys-arg 1))
	(vp-push (sys-arg 1))
	(assign '(rsp 1) (sys-args 2 1))
	(sys-call sys_read)
	(vp-pop r0)
	(assign '(r0) _2))

(defcfun sys-write (_1 _2)
	;fd, string, length
	(assign _1 (sys-args 3))
	(sys-call sys_write)
	(assign '(r0) _2))

(defcfun sys-write-char (_1 _2)
	;fd, char
	(assign _1 (sys-args 2))
	(vp-push (sys-arg 1))
	(assign '(rsp 1) (sys-args 2 1))
	(sys-call sys_write)
	(vp-free ptr_size)
	(assign '(r0) _2))

(defcfun sys-mmap (_1 _2)
	;addr, len, prot, flags, fd, pos
	(assign _1 (sys-args 6))
	(sys-call sys_mmap)
	(assign '(r0) _2))

(defcfun sys-mprotect (_1 _2)
	;addr, len, prot
	(assign _1 (sys-args 3))
	(sys-call sys_mprotect)
	(assign '(r0) _2))

(defcfun sys-munmap (_1 _2)
	;addr, len
	(assign _1 (sys-args 2))
	(sys-call sys_munmap)
	(assign '(r0) _2))

(defcfun sys-close (_1 _2)
	;fd
	(assign _1 (sys-args 1))
	(sys-call sys_close)
	(assign '(r0) _2))

(defcfun sys-ftruncate (_1 _2)
	;fd, offset
	(assign _1 (sys-args 2))
	(sys-call sys_ftruncate)
	(assign '(r0) _2))

(defcfun sys-fcntl (_1 _2)
	;fd, cmd, arg
	(assign _1 (sys-args 3))
	(sys-call sys_fcntl)
	(assign '(r0) _2))
