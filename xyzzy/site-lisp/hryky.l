;;------------------------------------------------------------------------------
;; @file        hryky.l
;; @brief       code snippets by xyzzy Lisp
;; @version     $Id: hryky.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
;;
;; usage:
;; 1. appends the load-path in siteinit.l
;;    The following example assumes that threre is hryky.l at
;;    %DEVROOT%/hryky-codebase/xyzzy/site-list/hryky.l
;; (setq *default-load-path*
;; 	  (cons
;; 	   (merge-pathnames
;; 		"hryky-codebase/xyzzy/site-lisp"
;; 		(substitute-string (si::getenv "DEVROOT") "\\\\" "/")
;; 		)
;; 	   *default-load-path*
;; 		)
;; 	  )
;;
;; 2. byte-compiles siteinit.l
;; 3. recreates xyzzy.***
;; 4. require hryky.l in .xyzzy
;; (require "hryky")
;;
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

(defpackage "hryky")

(require "hryky-align")
(require "hryky-common")
(require "hryky-search")
(require "hryky-template")

;;------------------------------------------------------------------------------
;; exported
;;------------------------------------------------------------------------------
(in-package "editor")
(export '(
		  load-xyzzy-config
		  toggle-cpp-source
		  enclose-as-comment-c
		  execute-file
		  delete-regexp-buffer
		  delete-name-buffer
		  cmake
		  msys
		  open-solution
		  build-solution
		  svn-update
		  svn-commit
		  svn-add
		  set-current-directory
		  )
		)

;;--------------------------------------
;; load .xyzzy
;;--------------------------------------
(defun load-xyzzy-config ()
  (interactive)
  (load-file "~/.xyzzy"))
(define-key ctl-x-map #\x 'load-xyzzy-config)

;;--------------------------------------
;; switch cpp <=> h
;;--------------------------------------
(defun toggle-cpp-source ()
  (interactive)
  (hryky-common::toggle-cpp-source)
  )
(define-key ctl-x-map '(#\t #\s) 'toggle-cpp-source)


;;--------------------------------------
;; encloses the word under the current position as C/C++ comment.
;;--------------------------------------
(defun enclose-as-comment-c ()
  (interactive)
  (hryky-template::enclose-as-comment-c))
(define-key spec-map #\o 'enclose-as-comment-c)

;;--------------------------------------
;; executes an executable file
;;--------------------------------------
(defun execute-file
  (filename args)
  (interactive "ffilename : \nsarguments : ")
  (if (hryky-common::is-empty filename) (setf filename (editor::get-buffer-file-name)))
  (execute-subprocess
   (format nil "\"~A ~A\"" filename args)
   nil
   (format nil "*~A*" (file-namestring filename))
   )
  )
  
;;--------------------------------------
;; deletes buffers which have the path matched by regular expression
;;--------------------------------------
(defun delete-regexp-buffer
  (regexp)
  (interactive "sregular expression : ")
  (hryky-common::delete-regexp-buffer regexp))

;;--------------------------------------
;; deletes buffers named as name[n].
;;--------------------------------------
(defun delete-name-buffer
  (name)
  (interactive "bbuffer : ")
  (map (quote list)
	   (function
		(lambda (buffer)
		  (delete-buffer buffer)
		  )
		)
	   (find-name-buffer (buffer-name name))
	   )
  )

;;--------------------------------------
;; cmake
;;--------------------------------------
(define-history-variable cmake-history nil)
(setf (get 'cmake 'ed::minibuffer-history-variable) 'cmake-history)
(defun cmake
  (source binary command target configuration)
  (interactive "Dsource : \nsbinary : \nscommand : \nstarget : \nsconfiguration : "
	:history0 'cmake)
  (execute-subprocess
   (format
	nil
	"set ~A=~A&set ~A=~A&set ~A=~A&set ~A=~A&set ~A=~A&~A"
	"CMAKE_SRC_DIR" source
	"CMAKE_BIN_DIR" binary
	"CMAKE_COMMAND" command
	"CMAKE_TARGET" target
	"CMAKE_CONFIG" configuration
	(editor::concat (si:getenv "DEVROOT") "/hryky-codebase/tool/build/cmake.bat")
	)
   ""
   "*cmake*"
   ""
   binary)
  )

;;--------------------------------------
;; msys
;;--------------------------------------
(defun msys
  (buffer)
  (interactive "sbuffer : ")
  (execute-subprocess
   (format 
	nil
	"~A"
	(editor::concat (si:getenv "DEVROOT") "/hryky-codebase/tool/misc/msys.bat")
	)
   ""
   (format nil "*~A*" buffer)
   )
  )

;;--------------------------------------
;; opens a solution file of Visual Studio.
;;--------------------------------------
(defun open-solution
  (solution)
  (interactive "fsolution : ")
  (execute-subprocess
   (format
	nil
	"~A \"~A\""
	(editor::concat (si:getenv "DEVROOT") "/hryky-codebase/tool/build/open_solution.bat")
	solution
	)
   ""
   (format nil "*~A*" (file-namestring solution))
   )
  )
  
;;--------------------------------------
;; builds a solution file of Visual Studion.
;;--------------------------------------
(defun build-solution
  (solution configuration platform target)
  (interactive "fsolution : \nsconfiguration : \nsplatform : \nstarget")
  (execute-subprocess
   (format
	nil
	"set DEVENVSLN=~A&set DEVENVCONFIG=~A&set DEVENVPLATFORM=~A&\"~A\""
	solution
	configuration
	platform
	target
	(editor::concat (si:getenv "DEVROOT") "/hryky-codebase/tool/build/build_solution.bat")
	)
   nil
   (format nil "*~A*" (file-namestring solution))
   )
  )

;;--------------------------------------
;; use Subversion
;;--------------------------------------
(defun svn-update (directory)
  (interactive "Ddirectory : ")
  (execute-subprocess
   (format nil "svn update ~A" directory)
   "" "*svn-update*")
  )
(defun svn-commit (directory)
  (interactive "Ddirectory : ")
  (execute-subprocess
   (format nil "svn commit ~A" directory)
   "" "*svn-commit*")
  )
(defun svn-add (directory)
  (interactive "Ddirectory : ")
  (execute-subprocess
   (format nil "svn add ~A" directory)
   "" "*svn-add*")
  )

;;--------------------------------------
;; configures the current directory.
;;--------------------------------------
(setf 
 (get 'set-current-directory 'ed::minibuffer-history-variable) 
 'editor::*minibuffer-directory-name-history*)
(defun set-current-directory (directory)
  (interactive "Ddirectory : " :history0 'set-current-directory)
  (editor::set-default-directory directory)
  (message "~A" directory)
  )

(in-package "hryky")

