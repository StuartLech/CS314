;;;
;;; Stub functions for DLX traps.
;;; 3a18656e1cea70504b905836dee14db0
;;; Ethan L. Miller, 1999.  Released to the public domain.
;;;
;;; The traps such as Open and Close
;;; (note the capital letters) are for use by user programs.  The traps
;;; with names such as open and close (lower case) are for use by the OS.
;;;

	.text
	.align 2

;;; The following are the traps to be used by user-level programs
;;;
		.text
	.align 2
.proc _Open
.global _Open
_Open:		
;;; Note that trap #0x213 actually causes a trap vector in the OS of
;;; 0x1213.  The same is true for other user traps.  Thus, a user trap
;;; with trap #0x240 will result in a trap vector of 0x1240 in the OS.
	trap	#0x213
	jr	r31
	nop
.endproc _Open

.proc _Close
.global _Close
_Close:		
	trap	#0x214
	jr	r31
	nop
.endproc _Close

.proc _Read
.global _Read
_Read:		
	trap	#0x210
	jr	r31
	nop
.endproc _Read

.proc _Write
.global _Write
_Write:		
	trap	#0x211
	jr	r31
	nop
.endproc _Write

.proc _Lseek
.global _Lseek
_Lseek:		
	trap	#0x212
	jr	r31
	nop
.endproc _Lseek

.proc _Putchar
.global _Putchar
_Putchar:		
	trap	#0x280
	jr	r31
	nop
.endproc _Putchar

.proc _Printf
.global _Printf
_Printf:		
	trap	#0x201
	jr	r31
	nop
.endproc _Printf

.proc _fork
   .global _fork
   _fork:
       trap    #0x430
       nop
       jr      r31
       nop
.endproc _fork

.proc _Getpid
.global _Getpid
_Getpid:
        trap    #0x431
	nop
        jr      r31
        nop
.endproc _Getpid
