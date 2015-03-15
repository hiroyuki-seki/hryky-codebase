;;------------------------------------------------------------------------------
;; @file        hryky-common.l
;; @brief       common definition of hryky-* packages
;; @version     $Id: hryky-common.l 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
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

(defpackage "hryky-common")

(in-package "hryky-common")

;;--------------------------------------
;; default author
;;--------------------------------------
(defvar *author-name* "HRYKY")

;; @brief   insert string to current position
;; @param   str is the inserted string.
;;
(defun insert-string
  (str)
  (editor::save-excursion
	;; (beginning-of-line)
	(editor::with-output-to-selected-buffer (format t str))
	)
  )

;;--------------------------------------
;; adds a prefix at the top of each line
;;--------------------------------------
(defun add-prefix
  (prefix lines)
  (if (is-empty lines) ""
	;; inserts the prefix between the end of the line and the beginning of the next line
	;; except for the end of the string.
	(editor::substitute-string
	 ;; appends the prefix at the beginning of the string.
	 (editor::substitute-string lines "^" prefix)
	 "\n\\(.\\)" (editor::concat "\n" prefix "\\1"))
	)
  )

;;--------------------------------------
;; adds the indent at the top of a line
;;--------------------------------------
(defun add-indent
  (lines)
  (add-prefix
   (get-indent) lines))

;;--------------------------------------
;; confirms whether the string is empty
;;--------------------------------------
(defun is-empty
  (str)
  (equal 0 (length str)))

;;--------------------------------------
;; retrieves the path of the current selected buffer.
;;--------------------------------------
(defun get-selected-path()
  (editor::get-buffer-file-name (editor::selected-buffer)))

;;--------------------------------------
;; retrieves the name of the path from the current buffer.
;;--------------------------------------
(defun get-file-name
  (&optional (path (hryky-common::get-selected-path)))
  (file-namestring path))

;;--------------------------------------
;; retrieves the name of the path.
;;--------------------------------------
(defun get-file-base-name
  (&optional (path (hryky-common::get-selected-path)))
  (labels
	  ((basename (prev result)
		 (if (string-equal prev result)
			 result
		   (basename result (pathname-name result))
		   )
		 ))
	(basename path (pathname-name path))
	)
  )

;;--------------------------------------
;; concatenates the elements of the list with a character.
;;--------------------------------------
(defun join
  (list &optional (chara ""))
  (if (rest list)
	  (editor::concat
	   (first list)
	   chara
	   (join (rest list) chara)
	   )
	(first list)
	)
  )

;;--------------------------------------
;; removes the last element of the list
;;--------------------------------------
(defun pop-back
  (list)
  (reverse (rest (reverse list))))

;;--------------------------------------
;; retrieves a character of white-space
;;--------------------------------------
(defun get-white-space()
  (char " " 0))

;;--------------------------------------
;; retrieves the TAB
;;--------------------------------------
(defun get-indent
  (&optional (num 1))
  (let ((ret-str ""))
	(dotimes (index num)
	  (setq ret-str (editor::concatenate 'string ret-str "\t"))
	  )
	ret-str)
  )
;;   (make-sequence
;;    'string
;;    (* num editor::*tab-columns*) :initial-element (get-white-space)))

;;--------------------------------------
;; retrieves the string which represents date and time.
;;--------------------------------------
(defun get-date-string()
  (editor::format-date-string "%Y-%m-%dT%H:%M:%S%Z")
  )
(defun get-date-string-hex()
  (string-upcase 
   (format nil "~X" (parse-integer (editor::format-date-string "%Y%m%d%H%M%S"))))
  )

;;--------------------------------------
;; retrieves the string of same characters
;;--------------------------------------
(defun get-chars
  (char num)
  (make-sequence 'string num :initial-element char))

;;--------------------------------------
;; confirms whether the string is "y".
;;--------------------------------------
(defun is-yes
  (str)
  (string-equal "y" str))

;;--------------------------------------
;; switches the file between .cpp <=> .h
;;--------------------------------------
(defun toggle-cpp-source ()
  (let ((filename (file-namestring (editor::get-buffer-file-name)))
		)
	(cond 
	 ((pathname-match-p filename "*.cpp")
	  (let ((dest (editor::substitute-string filename ".cpp$" ".h")))
		(if (editor::find-name-buffer dest)
			(editor::switch-to-buffer dest)
		  (message "~A is not found" dest))))
	 ((pathname-match-p filename "*.def.h")
	  (let ((dest (editor::substitute-string filename ".def.h$" ".h")))
		(if (editor::find-name-buffer dest)
			(editor::switch-to-buffer dest)
		  (message "~A is not found" dest))))
	 ((pathname-match-p filename "*.h")
	  (let ((cpp-dest (editor::substitute-string filename ".h$" ".cpp"))
			(def-dest (editor::substitute-string filename ".h$" ".def.h")))
		(cond ((editor::find-name-buffer cpp-dest)
			   (editor::switch-to-buffer cpp-dest))
			  ((editor::find-name-buffer def-dest)
			   (editor::switch-to-buffer def-dest))
			  (t (message "~A or ~A are not found" cpp-dest def-dest))))))))

;;--------------------------------------
;; deletes buffers which have the path matched by regular expression
;;--------------------------------------
(defun delete-regexp-buffer
  (regexp)
  (map (quote list)
	   (function
		(lambda (buffer)
		  (let ((buffer-filename (editor::get-buffer-file-name buffer)))
			(if (and
				 buffer-filename
				 (editor::string-match regexp buffer-filename)
				 )
				(editor::delete-buffer buffer)
			  )
			)
		  )
		)
	   (editor::buffer-list)
	   )
  )

;;--------------------------------------
;; moves the current pointion to the beginning of C/C++ definition
;;--------------------------------------
(defun c-beginning-of-defun ()
  (editor::goto-char (- (editor::point) 1))
  (if (editor::re-search-backward "^[^{ \t]*{" t)
	  (editor::goto-char (editor::point))
	(editor::goto-char (+ (editor::point) 1))))

;;--------------------------------------
;; moves the current pointion to the end of C/C++ definition
;;--------------------------------------
(defun c-end-of-defun ()
  (editor::goto-char (+ (editor::point) 1))
  (if (editor::re-search-forward "^[^} \t]*}" t)
	  (progn
		(editor::goto-char (+ (editor::point) (length (editor::match-string 0))))
		(editor::forward-line))
	(editor::goto-char (- (editor::point) 1))))

