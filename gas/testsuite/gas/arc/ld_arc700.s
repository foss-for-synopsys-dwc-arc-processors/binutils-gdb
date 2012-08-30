; Test ARC specific assembler errors
; 
; Copyright 2007-2012 Synopsys Inc.
; 
; This file is free software; you can redistribute it and/or modify it
; under the terms of the GNU General Public License as published by the
; Free Software Foundation; either version 3, or (at your option) any
; later version.
; 
; This file is distributed in the hope that it will be useful, but
; WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
; General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this program; see the file COPYING3.  If not see
; <http://www.gnu.org/licenses/>.  */
;
; { dg-do assemble { target arc-*-* } }

	ld	lp_count,[sp,4]	; { dg-error "ld operand error" }
	
	ld	ilink1,[sp,4]	; { dg-error "ld operand error" }

	ld	ilink2,[sp,4]	; { dg-error "ld operand error" }


		

