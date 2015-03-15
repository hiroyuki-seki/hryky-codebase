;;------------------------------------------------------------------------------
;; @file        hryky-align.l
;; @brief       aligns each line by inserting white spaces before the string specified regular expression.
;; @version     $Id: hryky-align.l 101 2012-09-30 12:50:52Z hryky.private@gmail.com $
;;------------------------------------------------------------------------------
#|
Copyright (c) 2011-2012 hryky.private@gmail.com

Permission is hereby granted, free of charge, to any person obtaining 
a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the 
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in 
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
THE SOFTWARE.
|#

(defpackage "hryky-align")
;;------------------------------------------------------------------------------
;; exported functions.
;;------------------------------------------------------------------------------
(in-package "editor")
(export '(align-by))
;;
;; @brief       aligns each line on the basis of the specified regular expression
;; @param       regexp is the regular expression that expresses aligned string.
;; @param       begin is the beginning point of the region which this function affects.
;; @param       end is the end point of the region which this function affects.
;;
;; example:
;; If (aling-by "[^ ]+;") applies to the following lines,
;;
;;   int foo;
;;   float const bar;
;;
;; the result is
;;
;;  int         foo;
;;  float const bar;
;;
;; If (aling-by "=.+;") applies to the following lines,
;;
;;  int foo = 0;
;;  float const bar = 1.0f;
;;
;; the result is
;;
;;  int foo         = 0;
;;  float const bar = 1.0f;
;;
(define-history-variable regexp-history nil)
(setf (get 'regexp 'ed::minibuffer-history-variable) 'regexp-history)
(defun align-by (regexp)
  (interactive "sregexp : " :default0 "[^ ]+?;" :history0 'regexp)
  (hryky-align::align regexp))
(define-key ctl-x-map '(#\a #\b) 'align-by)

;;------------------------------------------------------------------------------
;; internal functions.
;;------------------------------------------------------------------------------
(in-package "hryky-align")
;;--------------------------------------
;; aligns each line
;;--------------------------------------
(defun align
  (regexp 
   &optional 
   (begin (editor::region-beginning)) 
   (end (editor::region-end))
   )
  (editor::save-restriction
	(editor::save-excursion
	  (editor::narrow-to-region begin end)
	  (editor::goto-char (editor::point-min))
	  (let ((alignments
			 (create-alignments '() (editor::concat "\\(.+?\\)" regexp ".*?"))
			 )
			)
		(insert-white-space-before-alignment
		 alignments
		 (align-tab-columns (max-prefix-columns alignments))
		 )
		)
	  )
	)
  )
  
;;------------------------------------------------------------------------------
;; for internal use  
;;------------------------------------------------------------------------------


;; 
;; @brief       aligns the position of column to the unit position of tabs
;; @param       columns is the aligned position of column
;;
(defun align-tab-columns (columns)
  (* (editor::tab-columns) 
	 (truncate 
	  (/ 
	   (+ columns (- (editor::tab-columns) 1)) 
	   (editor::tab-columns)
	   )
	  )
	 )
  )
  
;;
;; @brief       creates the list of the positions into which white-space will be inserted.
;; @param       alignments is the list of the position (line . column).
;; @param       regexp is the regular expression which matches the alinged string.
;;
(defun create-alignments (alignments regexp)
  (if (editor::scan-buffer regexp :regexp t :no-dup t :tail t)
	  (cons
	   (editor::save-excursion
		 (editor::goto-char (editor::match-end 1))
		 (cons (editor::current-line-number) (editor::current-column))
		 )
	   (create-alignments alignments regexp)
	   )
	alignments)
  )

;;
;; @brief       outputs the list of the positions for debug use
;; @param       alignments is the list of the position
;;
(defun debug-alignments (alignments)
  (if (endp alignments)
	  (string "")
	(let ((region (car alignments)))
	  (concat
	   (format nil "[~D,~D]\n" (car region) (cdr region))
	   (debug-alignments (cdr alignments))
	   )
	  )
	)
  )

;;
;; @brief       retrieves the maximum length of the string preceding the aligned string.
;; @param       alignments is the list of the position.
;; @param       max-columns is the current maximum length.
;;
(defun max-prefix-columns (alignments &optional (max-columns 0))
  (if (endp alignments)
	  max-columns
	(let ((region (car alignments)))
	  (let ((region-columns (cdr region)))
		(if (< max-columns region-columns)
			(max-prefix-columns (cdr alignments) region-columns)
		  (max-prefix-columns (cdr alignments) max-columns))
		)
	  )
	)
  )

;;
;; @brief       inserts white-spaces before the each aligned string
;; @param       alignments is the list of the position.
;; @param       max-columns is the maximum length of the string preceding the aligned string.
;;
(defun insert-white-space-before-alignment (alignments max-columns)
  (if (endp alignments) t
	(let ((region (car alignments)))
	  (editor::goto-line (car region))
	  (editor::goto-column (cdr region))
	  (editor::with-output-to-selected-buffer
		(format
		 t 
		 (make-sequence 
		  'string 
		  (- max-columns (cdr region)) 
		  :initial-element (char " " 0)
		  )
		 )
		)
	  (insert-white-space-before-alignment (cdr alignments) max-columns)
	  )
	)
  )

