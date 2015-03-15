;;------------------------------------------------------------------------------
;; @file        hryky-search.l
;; @brief       searches words from current buffer
;; @version     $Id: hryky-search.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
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

(defpackage "hryky-search")
(in-package "hryky-search")

(defvar *search-words-begin* 0)
(defvar *search-words-end* 0)
(defvar *search-words* "")
 
;;--------------------------------------
;; @brief       appends a word to the string for searching
;;--------------------------------------
(defun append-word ()
  (editor::save-excursion
	(let ((current (editor::point)) (end 0))
	  (setf
	   end
	   (progn
		 (if (not (equal current *search-words-begin*))
			 (editor::goto-char current)
		   (editor::goto-char *search-words-end*))
		 (editor::forward-word)
		 (editor::point)
		 )
	   )
	  (setf *search-words* (editor::buffer-substring current end))
	  (message *search-words*)
	  (setf *search-words-begin* current)
	  (setf *search-words-end* end)
	  (editor::copy-region-to-clipboard current end)
	  )
	)
  )

;;--------------------------------------
;; @brief       searches the string forward in the current buffer
;;--------------------------------------
(defun search-words-forward ()
  (let ((pre-pos (editor::point)))
	(editor::forward-char)
	(editor::search-forward *search-words* t)
	(if (equal (+ pre-pos 1) (editor::point))
		(editor::goto-char pre-pos)
	  )
	)
  )

;;--------------------------------------
;; @brief       searches the string backward in the current buffer
;;--------------------------------------
(defun search-words-backward ()
  (let ((pre-pos (editor::point)))
	(editor::backward-char)
	(editor::search-backward *search-words* t)
	(if (equal (- pre-pos 1) (editor::point))
		(editor::goto-char pre-pos)
	  )
	)
  )
  
;;------------------------------------------------------------------------------
;; exported functions.
;;------------------------------------------------------------------------------

(in-package "editor")

;;--------------------------------------
;; appends a word to the string for searching
;;--------------------------------------
(defun append-search-word ()
  (interactive)
  (hryky-search::append-word)
  )
(editor::define-key esc-map '#\C-l 'append-search-word)

;;--------------------------------------
;; searches forward the string in the current buffer 
;;--------------------------------------
(defun search-words-forward ()
  (interactive)
  (hryky-search::search-words-forward)
  )
(editor::define-key esc-map '#\PageDown 'search-words-forward)

;;--------------------------------------
;; searches backward the string in the current buffer 
;;--------------------------------------
(defun search-words-backward ()
  (interactive)
  (hryky-search::search-words-backward)
  )
(editor::define-key esc-map '#\PageUp 'search-words-backward)


