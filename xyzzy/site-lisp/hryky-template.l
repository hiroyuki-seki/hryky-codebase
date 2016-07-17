;;------------------------------------------------------------------------------
;; @file        hryky-template.l
;; @brief       inserts the archetype of program sources
;; @version     $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
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
(defpackage "hryky-template")
(require "hryky-common")
;;------------------------------------------------------------------------------
;; exported
;;------------------------------------------------------------------------------
(in-package "editor")
(export '(insert-c-source
		  insert-cpp-source
		  insert-cpp-class-source
		  insert-cpp-test
		  insert-c-header
		  insert-cpp-header
		  insert-cpp-class-header
		  insert-cpp-func
		  insert-cpp-memfunc
		  insert-cpp-default-constructor
		  insert-cpp-copy-constructor
		  insert-cpp-move-constructor
		  insert-cpp-constructor
		  insert-cpp-destructor
		  insert-cpp-assignment-operator
		  insert-cpp-clear
		  insert-cpp-swap
		  insert-cpp-write-to
		  insert-cpp-swapfunc
		  insert-c-struct
		  insert-cpp-struct
		  insert-cpp-class
		  insert-ruby-class
		  insert-ruby-method
		  insert-ruby-source
		  ;;	insert-date-string
		  ;;	insert-author
		  insert-include-guard
		  insert-namespace-definition
		  )
		)

;;
;; @brief   inserts the archetype of C language source.
;; @param   desc is the description for C source file.
;;
(defun insert-c-source
  (desc)
  (interactive "sdescription : ")
  (hryky-common::insert-string
   (hryky-template::get-c-source desc)
   )
  )

;;
;; @brief   inserts the archetype of C++ source.
;; @param   desc is the description for C++ source file.
;; @param   namespace is the main namespace to which this C++ source belongs.
;;
(defun insert-cpp-source
  (desc namespace)
  (interactive "sdescription : \nsnamespace : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-source desc namespace)
   )
  )

;;
;; @brief   inserts the archetype of C++ source for declaration of class.
;; @param   desc is the description for C++ Source and Class.
;; @param   args is the definition of arguments separated by comma.
;; @param   baseclass is the name of base class.
;; @param   namespace is the main namespace defined in this file.
;; @param   classname is the name of Class defined in this file.
;; @param   typenames is the comma-separated list of template parameters.
;;
(defun insert-cpp-class-source
  (desc args baseclass namespace classname typenames)
  (interactive 
	  "sdescription : \nsarguments : \nsbase class : \nsnamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-class-source 
	namespace 
	classname 
	desc 
	args
	typenames
	baseclass)
   )
  )

;;
;; @brief   inserts the archtype of C++ source for testing.
;; @param   desc is the description for testing.
;;
(defun insert-cpp-test
  (desc)
  (interactive "sdescription : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-test
	desc
	)
   )
  )

;;
;; @brief   inserts the archetype of C languate header.
;; @param   desc is the description for this C file.
;;
(defun insert-c-header
  (desc)
  (interactive "sdescription : ")
  (hryky-common::insert-string (hryky-template::get-c-header desc))
  )

;;
;; @brief   inserts the archetype of C++ header.
;; @param   namespace is the main namespace defined in this file.
;;
(defun insert-cpp-header
  (desc namespace)
  (interactive "sdescription : \nsnamespace : ")
  (hryky-common::insert-string (hryky-template::get-cpp-header namespace desc))
  )

;;
;; @brief   inserts the archetype of C++ header for declaration of class.
;; @param   desc is the description for C++ Source and Class.
;; @param   args is the definition of arguments separated by comma.
;; @param   baseclass is the name of base class.
;; @param   namespace is the namespace of the class.
;; @param   classname is the name of Class defined in this file.
;; @param   typenames is the comma-separated list of template parameters.
;;
(defun insert-cpp-class-header
  (desc args baseclass namespace classname typenames)
  (interactive "sdescription : \nsarguments : \nsbase class : \nsnamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-class-header 
	args 
	namespace 
	classname 
	desc 
	typenames
	baseclass)
   )
  )

;;
;; @brief   inserts the archetype of the definition of C++ function.
;; @param   desc is the description for the function.
;; @param   funcname is the name of the function.
;; @param   rettype is the type of returned value.
;; @param   args is the definition of arguments separated by comma.
;; @param   namespace is the main namespace defined in this file.
;; @param   typenames is the comma-separated list of template parameters.
;;
(defun insert-cpp-func
  (desc funcname rettype args namespace typenames)
  (interactive
	  "sdescription : \nsfunction : \nsreturn type : \nsarguments : \nsnamespace : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-func
	namespace 
	funcname 
	desc 
	rettype 
	args 
	typenames
	:is-prototype t)
   )
  )

;;
;; @brief   inserts the archetype of the member function of C++ class.
;; @param   desc is the description for the function.
;; @param   funcname is the name of the function.
;; @param   rettype is the type of returned value of the function.
;; @param   args is the list of arguments separated by comma.
;; @param   is-virtual specified whether this function is virtual. [y|n]
;; @param   is-static specified whether this function is static. [y|n]
;; @param   is-const specified whether this function is const. [y|n]
;; @param   namespace is the namespace of the function.
;; @param   classname is the name of Class defined in this file.
;; @param   typenames is the comma-separated list of template parameters.
;;
(defun insert-cpp-memfunc
  (desc funcname rettype args is-virtual is-static is-const namespace classname typenames)
  (interactive
	  "sdescription : \nsfunction : \nsreturn type : \nsarguments : \nsvirtual? : \nsstatic? : \nsconst? : \nsnamespace : \nsclass : \nstemplate parameters : "
	:default4 "n" :default5 "n" :default6 "n"
	)
  (hryky-common::insert-string
   (hryky-template::get-cpp-memfunc
	namespace
	classname
	funcname
	desc
	rettype
	args
	typenames
	:is-virtual (hryky-common::is-yes is-virtual)
	:is-static (hryky-common::is-yes is-static)
	:is-const (hryky-common::is-yes is-const)
	:is-prototype t)
   )
  )

;;
;; @brief   inserts a definition of default constructor.
;; @param   baseclass is the name of base class.
;; @param   namespace is the namespace of the class.
;; @param   classname is the name of Class.
;; @param   typenames is the comma-separated list of template parameters.
;;
(defun insert-cpp-default-constructor
  (baseclass namespace classname typenames)
  (interactive "sbase class : \nsnamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-default-constructor 
	namespace 
	classname 
	typenames
	baseclass
	:is-prototype t)
   )
  )
  
;;
;; @brief   inserts a definition of copy constructor.
;; @param   baseclass is the name of base class.
;; @param   namespace is the namespace of the class.
;; @param   classname is the name of Class.
;; @param   typenames is the comma-separated list of template parameters.
;;
(defun insert-cpp-copy-constructor
  (baseclass namespace classname typenames)
  (interactive "sbase class : \nsnamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-copy-constructor 
	namespace 
	classname 
	typenames
	baseclass
	:is-prototype t)
   )
  )
  
;;
;; @brief   inserts a definition of move constructor.
;; @param   baseclass is the name of base class.
;; @param   namespace is the namespace of the class.
;; @param   classname is the name of Class.
;; @param   typenames is the comma-separated list of template parameters.
;;
(defun insert-cpp-move-constructor
  (baseclass namespace classname typenames)
  (interactive "sbase class : \nsnamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-move-constructor 
	namespace 
	classname 
	typenames
	baseclass
	:is-prototype t)
   )
  )
  
;;
;; @brief   inserts a definition of constructor
;; @param   args is the list of the declarations of argument
;; @param   baseclass is the name of base class.
;; @param   namespace is the namespace of the class.
;; @param   classname is the name of Class.
;; @param   typenames is the comma-separated list of template parameters.
;;
(defun insert-cpp-constructor
  (desc args baseclass namespace classname typenames)
  (interactive "sdescription : \nsarguments : \nsbase class : \nsnamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-constructor 
	namespace 
	classname 
	args
	desc
	typenames
	baseclass
	:is-prototype t)
   )
  )
  
;;
;; @brief   inserts a definition of destructor
;; @param   namespace is the namespace of the class.
;; @param   classname is the name of Class.
;; @param   typenames is the list of template parameters.
;;
(defun insert-cpp-destructor
  (namespace classname typenames)
  (interactive "snamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-destructor 
	namespace 
	classname 
	typenames
	:is-singleton nil
	:is-prototype t
	)
   )
  )
  
;;
;; @brief   inserts a definition of assignment operator
;; @param   namespace is the namespace of the class.
;; @param   classname is the name of class.
;; @param   typenames is the list of template parameters.
;;
(defun insert-cpp-assignment-operator
  (namespace classname typenames)
  (interactive "snamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-assignment-operator 
	namespace 
	classname 
	typenames
	:is-prototype t
	)
   )
  )
  
;;
;; @brief   inserts a definition of reseting an instance
;; @param   baseclass is the name of base class.
;; @param   namespace is the namespace of the class.
;; @param   classname is the name of class.
;; @param   typenames is the list of template parameters.
;;
(defun insert-cpp-clear
  (baseclass namespace classname typenames)
  (interactive "sbase class : \nsnamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-clear 
	namespace 
	classname 
	typenames
	baseclass
	:is-prototype t
	)
   )
  )
  
;;
;; @brief   inserts a definition of exhanging internal resources
;; @param   baseclass is the name of base class.
;; @param   namespace is the namespace of the class.
;; @param   classname is the name of class.
;; @param   typenames is the list of template parameters.
;;
(defun insert-cpp-swap
  (baseclass namespace classname typenames)
  (interactive "sbase class : \nsnamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-swap 
	namespace 
	classname 
	typenames
	baseclass
	:is-prototype t
	)
   )
  )
  
;;
;; @brief   inserts a definition of outputing the formatted information.
;; @param   baseclass is the name of base class.
;; @param   namespace is the namespace of the class.
;; @param   classname is the name of class.
;; @param   typenames is the list of template parameters.
;;
(defun insert-cpp-write-to
  (baseclass namespace classname typenames)
  (interactive "sbase class : \nsnamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-write-to 
	namespace 
	classname 
	typenames
	baseclass
	:is-prototype t
	)
   )
  )

;;
;; @brief   inserts a definition of swap function as no-member function.
;; @param   namespace is the namespace of the class.
;; @param   classname is the name of class.
;; @param   typenames is the list of template parameters.
;;
(defun insert-cpp-swapfunc
  (namespace classname typenames)
  (interactive "snamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-swapfunc 
	namespace 
	classname 
	typenames
	:is-prototype t
	)
   )
  )

;;--------------------------------------
;; inserts the archetype of the declaration of C language structure.
;;--------------------------------------
(defun insert-c-struct
  (structname &optional (desc ""))
  (interactive "sstruct : \nsdescription : ")
  (hryky-common::insert-string
   (hryky-template::get-c-struct structname desc)
   )
  )

;;--------------------------------------
;; inserts the archetype of the declaration of C++ structure.
;;--------------------------------------
(defun insert-cpp-struct
  (desc structname namespace)
  (interactive "sdescription : \nsstruct : \nsnamespace : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-struct desc structname namespace)))

;;
;; @brief   inserts the archetype of the declaration of C++ class.
;; @param   desc is the description for C++ Class.
;; @param   args is the list of the definitions of each argument separated by comma.
;; @param   baseclass is the name of base class.
;; @param   namespace is the main namespace defined in this file.
;; @param   classname is the name of Class defined in this file.
;; @param   typenames is the list of template parameters.
;;
(defun insert-cpp-class
  (desc args baseclass namespace classname typenames)
  (interactive
	  "sdescription : \nsarguments : \nsbase class : \nsnamespace : \nsclass : \nstemplate parameters : ")
  (hryky-common::insert-string
   (hryky-template::get-cpp-class
	args
	namespace
	classname
	desc
	typenames
	baseclass
	:is-prototype t)
   )
  )

;;--------------------------------------
;; inserts the archetype of the definition of Ruby class.
;;--------------------------------------
(defun insert-ruby-class
  (name desc)
  (interactive "sclass : \nsdescription : ")
  (hryky-common::insert-string
   (hryky-template::get-ruby-class name desc)
   )
  )

;;--------------------------------------
;; inserts the archetype of the definition of Ruby method.
;;--------------------------------------
(defun insert-ruby-method
  (name desc)
  (interactive "sname : \nsdescription : ")
  (hryky-common::insert-string 
  (hryky-template::get-ruby-method name desc)
   )
  )

;;--------------------------------------
;; inserts the archetype of Ruby source.
;;--------------------------------------
(defun insert-ruby-source
  (desc)
  (interactive "sdescription : ")
  (hryky-common::insert-string
   (hryky-template::get-ruby-source desc)
   )
  )

;;--------------------------------------
;; inserts date and time
;;--------------------------------------
(defun insert-date-string
  ()
  (interactive)
  (hryky-common::insert-string (hryky-common::get-date-string))
  )
(editor::define-key esc-map '#\F3 'insert-date-string)

;;--------------------------------------
;; inserts the name of the author
;;--------------------------------------
(defun insert-author
  ()
  (interactive)
  (hryky-common::insert-string hryky-common::*author-name*))
(editor::define-key esc-map '#\F2 'insert-author)

;;
;; @brief   inserts the definition of namespace
;; @param   namespace is the string concatenating each namespace by '::'
;;
(defun insert-namespace-definition
  (namespace)
  (interactive "snamespace : ")
  (hryky-common::insert-string
   (hryky-template::get-namespace-definition
	(hryky-template::get-namespace namespace))
   )
  )
  
;; 
;; @brief   inserts the include-guard
;;
(defun insert-include-guard
  ()
  (interactive)
  (hryky-common::insert-string (hryky-template::get-include-guard)))

;;------------------------------------------------------------------------------
;; internal
;;------------------------------------------------------------------------------
(in-package "hryky-template")
;;--------------------------------------
;; default length of a line
;;--------------------------------------
(defvar *row-length-max* 80)

;;--------------------------------------
;; default namespace
;;--------------------------------------
(defvar *default-namespace* "hryky")

;;--------------------------------------
;; default template parameters
;;--------------------------------------
(defvar *default-template-param* "hryky_template_param")

;;--------------------------------------
;; default template arguments
;;--------------------------------------
(defvar *default-template-arg* "hryky_template_arg")

;;--------------------------------------
;; specifies the use of default template parameters
;;--------------------------------------
(defvar *default-template-specifier* "*")

;;--------------------------------------
;; assigns the default namespace
;;--------------------------------------
(defun set-default-namespace
  (namespace)
  (setf *default-namespace* namespace))

;;--------------------------------------
;; default string which represents null pointer
;;--------------------------------------
(defvar *nullptr* "HRYKY_NULL")

;;--------------------------------------
;; default name of base class
;;--------------------------------------
(defvar *default-baseclass* "base_type")

;;--------------------------------------
;; assigns the default name of base class.
;;--------------------------------------
(defun set-default-baseclass
  (baseclass)
  (setf *default-baseclass* baseclass)
  )
  
;;--------------------------------------
;; default name of precompiled header
;;--------------------------------------
(defvar *precompiled-header* "precompiled.h")
  
;;------------------------------------------------------------------------------
;; inserts templates
;;------------------------------------------------------------------------------

;;--------------------------------------
;; retrieves the name of base class.
;;--------------------------------------
(defun get-baseclass (baseclass) baseclass)

;;--------------------------------------
;; default name of class
;;--------------------------------------
(defvar *default-classname* "")

;;--------------------------------------
;; assigns the name of default class
;;--------------------------------------
(defun set-default-classname
  (classname)
  (setf *default-classname* classname))

;;--------------------------------------
;; retrieves the name of class
;;--------------------------------------
(defun get-classname
  (classname namespace)
  (if (hryky-common::is-empty classname)
	  (if (hryky-common::is-empty *default-classname*)
		  (get-classname-from-path (hryky-common::get-selected-path) namespace)
		*default-classname*)
	classname)
  )

;;--------------------------------------
;; guesses the name of class based on the name of path
;;--------------------------------------
(defun get-classname-from-path
  (path namespace)
  (when path
	;; removes the part of namespaces
	(editor::substitute-string
	
	 ;; removes white-spaces.
	 (remove
	  (hryky-common::get-white-space)
	  ;; capitalizes each word.
	  (string-capitalize
	   ;; replaces to white-space except for alphabet and number.
	   (replace-to-c-identifier
		;; retrieves the name of file except for the extension.
		(hryky-common::get-file-base-name path)
		(hryky-common::get-white-space)
		)
	   )
	  )
	 
	 ;; creates pattern based on the namespaces.
	 (format
	  nil "^~A"
	  ;; concatenates the list of strings.
	  ;;(editor::concat-string-list
	  (hryky-common::join
	   ;; removes default namespace.
	   (rest
		;; splits the sequence of namespaces
		(editor::split-string
		 ;; retrieves a sequence of namespaces
		 (get-namespace namespace)
		 #\:)
		)
	   )
	  )
	 
	 "" :case-fold t)
	)
  )

;;--------------------------------------
;; guess the namespace based on the name of path
;;--------------------------------------
(defun get-namespace-from-path
  (&optional (path ""))
  ;; assigns the path of current buffer if the argument is empty.
  (if (hryky-common::is-empty path) (setf path (hryky-common::get-selected-path)))
  (let ((namespaces))
	(setf
	 namespaces
	 ;; remove invalid namespace
	 (remove-invalid-last-namespace
	  ;; splits the filename into the list.
	  (editor::split-string (hryky-common::get-file-base-name path) #\_)
	  )
	 )
  ;; shapes the namespaces
  (hryky-common::join
   ;; appends default namespace at the beginning.
   (cons
	*default-namespace*
	;; removes the last invalid element of the list.
	(hryky-common::pop-back namespaces)
	)
   "::"
   )
	)
  )

;;--------------------------------------
;; retrieves the first part of include-guard.
;;--------------------------------------
(defun get-include-guard-header
  (&optional (include-guard ""))
  (if (hryky-common::is-empty include-guard)
	  (setf include-guard (get-include-guard)))
  (editor::concat
   (format nil "#ifndef ~A\n" include-guard)
   (format nil "#define ~A\n" include-guard)))

;;--------------------------------------
;; retrieves the last part of include-guard.
;;--------------------------------------
(defun get-include-guard-footer
  (&optional (include-guard ""))
  (if (hryky-common::is-empty include-guard)
	  (setf include-guard (get-include-guard)))
  (format nil "#endif // ~a\n" include-guard))

;;--------------------------------------
;; retrieves the comment of C/C++ file.
;;--------------------------------------
(defun get-c-file-comment
  (desc)
  (editor::concat
   (format nil "/**\n")
   (format nil "  @file     ~A\n" (hryky-common::get-file-name))
   (format nil "  @brief    ~A.\n" desc)
   (format nil "  @author   ~A\n" hryky-common::*author-name*)
   (format nil "  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $\n")
   (format nil " */\n")
   )
  )

;;--------------------------------------
;; retrieves the comment of C/C++ with additional description.
;;--------------------------------------
(defun get-c-comment
  (desc &optional (include ""))
  (editor::concat
   (format nil "/**\n")
   (format nil "  @brief ~A.\n" desc)
   include
   (format nil " */\n")))

;;--------------------------------------
;; retrieves the archetype of C language source
;;--------------------------------------
(defun get-c-source
  (desc)
  (editor::concat
   (get-c-file-comment desc)
   (get-c-comment-block "macro")
   (get-c-comment-block "declares functions")
   (get-c-comment-block "defines global variable")
   (get-c-comment-block "defines global functions")
   (get-c-comment-block "defines static functions")
   (format nil "// end of file\n")
   )
  )

;;--------------------------------------
;; retrieves the archetype of C++ source
;;--------------------------------------
(defun get-cpp-source
  (desc namespace)
  
  ;; refines the namespace.
  (setf namespace (get-namespace namespace))
  
  (editor::concat
   (get-c-file-comment desc)
   (get-cpp-precompile-include)
   (get-cpp-header-include)
   (get-c-comment-block "macro")
   (get-c-comment-block "anonymous namespace")

   (get-namespace-definition 
	namespace
	(get-namespace-definition "")
	)

   (get-c-comment-block "defines global functions")
   (get-c-comment-block "defines static functions")

   (get-namespace-definition 
	namespace
	(get-namespace-definition "")
	)

   (get-c-comment-block "explicit instantiation")

   (format nil "// end of file\n")
   )
  )

;;--------------------------------------
;; retrieves the archetype of C++ test
;;--------------------------------------
(defun get-cpp-test
  (desc)

  (editor::concat
   (get-c-file-comment desc)
   (get-cpp-precompile-include)
   (get-cpp-include "hryky/testing.h")
   (get-c-comment-block "macro")
   (get-c-comment-block "anonymous namespace")

   (get-namespace-definition
	(get-namespace)
	(get-namespace-definition
	 ""
	 (hryky-common::add-indent
	  (editor::concat
	   (format nil "// enretisters a test.\n")
	   (format nil "class Test : testing::unit::Base\n")
	   (format nil "{\n")
	   (format nil "public:\n")
	   (hryky-common::add-indent
		(editor::concat
		 (format nil "typedef testing::unit::Base base_type;\n")
		 (format nil "typedef Test this_type;\n\n")
		 (format nil "/// constructor.\n")
		 (format nil "Test();\n\n")
		 )
		)
	   (format nil "private:\n")
	   (hryky-common::add-indent
		(editor::concat
		 (format nil "Test(this_type const &);\n")
		 (format nil "this_type & operator=(this_type const &);\n\n")
		 (format nil "/// ~A.\n" desc)
		 (format nil "virtual bool run_impl();\n\n")
		 )
		)
	   (format nil "};\n")
	   (format nil "Test const g_test;\n\n")
	   (format nil "char const * const g_testname = \"~A\";\n\n"
			   (editor::substitute-string
				(hryky-common::get-file-base-name)
				"test_\\(.*\\)" "\\1"))
	   )
	  )
	 )
	)

   (get-namespace-definition
	(get-namespace)
	(get-namespace-definition
	 ""
	 (editor::concat
	  (get-c-comment-block "public member functions of Test")
	  (get-cpp-memfunc-header
	   " " 
	   "Test" 
	   "Test" 
	   "constructor" 
	   "" 
	   "" 
	   "")
	   (hryky-common::add-indent
		(format nil ": base_type(g_testname)\n")
		)
	  (format nil "{\n")
	  (format nil "}\n")
	  
	  (get-c-comment-block "private member functions of Test")
	  (get-cpp-memfunc-header
	   " " 
	   "Test" 
	   "run_impl" 
	   desc 
	   "bool" 
	   "" 
	   "")
	  (format nil "{\n")
	  (hryky-common::add-indent
	   (editor::concat
		(format nil "// initializes logging.\n")
		(format nil "testing::Log log(*this);\n\n")
		
		(format nil "// initializes the generator of pseudo random number.\n")
		(format nil "testing::Random random;\n")
		(format nil "log.writer() << hryky_stream_denote(random);\n\n")
		
		(format nil "return true;\n")
		)
	   )
	  (format nil "}\n")
	  )
	 )
	)
   )
  )

;;--------------------------------------
;; retreives the archetype of C++ source for declaration of class
;;--------------------------------------
(defun get-cpp-class-source
  (namespace 
  classname 
  desc 
  args 
  &optional
   (typenames "")
   (baseclass *default-classname*)
  &key 
   ((:is-instantiate is-instantiate) nil)
   ((:is-singleton is-singleton) nil)
  )

  ;; refines the namespace.
  (setf namespace (get-namespace namespace))
  ;; refines the name of class.
  (setf classname (get-classname classname namespace))
  ;; refines the name of base class.
  (setf baseclass (get-baseclass baseclass))
  
  (editor::concat
   (get-c-file-comment desc)
   (get-cpp-precompile-include)
   (get-cpp-header-include)
   (get-c-comment-block "macro")
   (get-c-comment-block "anonymous namespace")

   (get-namespace-definition
	namespace
	(get-namespace-definition
	 ""
	 (hryky-common::add-indent
	  (editor::concat
	   ""
	   ;; defines the pointer for singleton instance.
	   (if is-singleton
		   (editor::concat
			(format nil "/// singleton.\n")
			(format
			 nil "~A * g_instance = 0;\n\n"
			 (get-template-classname namespace classname typenames))
			)
		 )
	   )
	  )
	 )
	)

   (get-c-comment-block "static variable")
   (get-c-comment-block "function prototype")
   (get-c-comment-block "defines public member functions")

   (if is-instantiate
	   ;; insert static member functions to instantiate object
	   (get-cpp-instantiate namespace classname args typenames )
	 )

   (if is-singleton 
	   (editor::concat
		;; retrieves the first part of the definition to get the instance.
		(get-cpp-memfunc-header
		 namespace
		 classname
		 "instance"
		 "retrieve the existing instance"
		 (editor::concat
		  (get-template-classname
		   namespace
		   classname
		   typenames
		   )
		  "::instance_type\n"
		  )
		 ""
		 typenames
		 :is-static t
		 )
		;; appends the entity of the definition.
		(format nil "{\n")
		(hryky-common::add-indent
		 (editor::concat
		  (format nil "if (~A == g_instance)\n" *nullptr*)
		  (format nil "\tlog::alert(\"~A is not initialized.\\n\");\n\n"
				  (get-template-classname namespace classname typenames))
		  (format nil "return share_ptr(g_instance);\n")
		  )
		 )
		(format nil "}\n")
		)
	 )

   (if is-instantiate
	   ;; appends member functions to release object.
	   (get-cpp-release namespace classname baseclass))

   ;; appends the definition of the default constructor.
   (get-cpp-default-constructor namespace classname typenames baseclass)
	
   ;; appends the definition of the copy constructor.
   (get-cpp-copy-constructor
	namespace classname typenames baseclass)

   ;; appends the definition of the move constructor.
   (get-cpp-move-constructor
	namespace classname typenames baseclass)

   ;; appends the definition of the constructor.
   (if (not (hryky-common::is-empty args))
	   (get-cpp-constructor
		namespace
		classname
		args
		"constructor"
		typenames
		baseclass)
	 )
	
   ;; appends the definition of the destructor.
   (get-cpp-destructor
	namespace
	classname
	typenames
	:is-prototype nil
	:is-singleton is-singleton)
   
   ;; appends the definition of clearing the internal resources.
   (get-cpp-clear namespace classname typenames baseclass)

   ;; appends the defintion of interchanging the internal resources.
   (get-cpp-swap namespace classname typenames baseclass)

   (get-c-comment-block "defines protected member functions")

   ;; appends the function for initialization.
   (if is-instantiate
	   (get-cpp-initialize args namespace classname typenames baseclass)
	 )
	 
   (get-c-comment-block "defines private member functions")
   
   (get-c-comment-block "defines global functions")
   
   (get-c-comment-block "defines functions used in this file")
   (get-namespace-definition
	namespace
	(get-namespace-definition "")
	)

   (get-c-comment-block "explicit instantiation")

   (format nil "// end of file\n")
   )
  )

;;--------------------------------------
;; retrieves the archetype of C languate header.
;;--------------------------------------
(defun get-c-header
  (desc)
  (let ((include-guard (get-include-guard)))
	(editor::concat
	 (get-c-file-comment desc)
	 (get-include-guard-header include-guard)
	 (get-c-comment-block "macro definition")
	 (get-c-comment-block "struct declaration")

	 (format nil "#ifdef __cplusplus\n")
	 (format nil "extern \"C\" {\n")
	 (format nil "#endif\n\n")

	 (get-c-comment-block "function prototype")

	 (format nil "\n#ifdef __cplusplus\n")
	 (format nil "}\n")
	 (format nil "#endif\n")
	 (get-include-guard-footer include-guard)
	 (format nil "// end of file\n")
	 )
	)
  )

;;--------------------------------------
;; retrieves the archetype of C++ header
;;--------------------------------------
(defun get-cpp-header
  (namespace desc)
  (setf namespace (get-namespace namespace))
  (let ((include-guard (get-include-guard)))
	(editor::concat
	 (get-c-file-comment desc)
	 (get-include-guard-header include-guard)

	 (get-c-comment-block "defines macros")
	 (get-c-comment-block "declares types")

	 (get-namespace-definition namespace)

	 (get-c-comment-block "declares classes")
	 (get-c-comment-block "declares global functions")
	 (get-namespace-definition namespace)

	 (get-c-comment-block "defines global functions")

	 (get-include-guard-footer include-guard)
	 (format nil "// end of file\n")
	 )
	)
  )
  

;;--------------------------------------
;; retrieves the archetype of C++ header for declaration of class
;;--------------------------------------
(defun get-cpp-class-header
  (
   args
   namespace
   classname
   desc
   typenames
   baseclass
   &key
   ((:is-singleton is-singleton) nil)
   )
  ;; refines the namespace.
  (setf namespace (get-namespace namespace))
  ;; refines the name of class
  (setf classname (get-classname classname namespace))

  (let ((include-guard (get-include-guard)))

	(editor::concat
	 ;; appends the comment of the header of the file.
	 (get-c-file-comment desc)
	 ;; appends the first part of the include-guard.
	 (get-include-guard-header include-guard)

	 ;; (if (hryky-common::is-empty (editor::substitute-string baseclass "\\(hryky::\\)?NoHeap" ""))
	 ;;    (format nil "#include \"misc/no_heap.h\"\n")
	 ;;  (if (hryky-common::is-empty (editor::substitute-string baseclass "\\(hryky::\\)?Heap" ""))
	 ;;      (format nil "#include \"misc/heap.h\"\n")))

	 (get-c-comment-block "defines macros")
	 
	 (if (not (hryky-common::is-empty typenames))
		 (editor::concat 
		  (format nil "#define ~A \\\n" *default-template-param*)
		  (hryky-common::add-indent (format nil "~A\n" typenames))
		  (format nil "#define ~A \\\n" *default-template-arg*)
		  (hryky-common::add-indent 
		   (format nil "~A\n" (get-template-arguments-entity typenames))
		   )
		  )
	   )
	 
	 (get-c-comment-block "declares types")

	 ;; appends the definition of namespace.
	 (get-namespace-definition
	  namespace
	  (hryky-common::add-indent
	   (editor::concat
		(format nil "/// ~A.\n" desc)
		(get-default-template-declaration typenames)
		(format nil "class ~A;\n\n" classname)
		)
	   )
	  )

	 (get-c-comment-block "declares classes")

	 ;; retrieves the definition of the class.
	 (get-cpp-class 
	  args 
	  namespace 
	  classname 
	  desc 
	  typenames
	  baseclass 
	  :is-singleton is-singleton
	  )

	 (get-c-comment-block "specializes classes")
	 (get-namespace-definition namespace)

	 (get-c-comment-block "defines public member functions")
	 ;; appends the defintion of formatting the information as string.
	 (get-cpp-write-to 
	  namespace 
	  classname 
	  (if (hryky-common::is-empty typenames)
		  ""
		*default-template-specifier*)
	  baseclass)

	 (get-c-comment-block "defines protected member functions")
	 (get-c-comment-block "defines private member functions")

	 (get-c-comment-block "declares global functions")
	 (get-namespace-definition namespace)

	 (get-c-comment-block "defines global functions")
	 
	 (if (not (hryky-common::is-empty typenames)) 
		 (editor::concat
		  (get-c-comment-block "revokes the temporary macros")
		  (format nil "#undef ~A\n" *default-template-param*)
		  (format nil "#undef ~A\n" *default-template-arg*)
		  )
	   )

	 ;; appends the last part of the include-guard.
	 (get-include-guard-footer include-guard)

	 (format nil "// end of file\n")
	 )
	)
  )

;;--------------------------------------
;; retrieves the archetype of the defintion of C++ function.
;;--------------------------------------
(defun get-cpp-func
  (namespace 
   funcname 
   desc 
   rettype 
   args 
   typenames
   &key
   ((:is-prototype is-prototype) nil)
   )
  (editor::concat
   (get-cpp-func-header
	namespace 
	funcname 
	desc 
	rettype 
	args 
	typenames
	:is-prototype is-prototype)
   (format nil "{\n~Areturn;\n}\n" (hryky-common::get-indent))
   )
  )
  
;;--------------------------------------
;; retrieves the first part of the definition of function
;;--------------------------------------
(defun get-cpp-func-header
  (namespace 
   funcname 
   desc 
   rettype 
   args 
   typenames
   &key
   ((:is-prototype is-prototype) nil)
   )
  
  (editor::concat
   (get-c-comment
	desc
	;; appends the prototype declaration.
	(if is-prototype
		(hryky-common::add-indent
		 (editor::concat
		  (get-prototype-desc desc)
		  (get-template-declaration typenames)
		  (format
		   nil "~A\n\n"
		   (get-prototype-function funcname rettype args)
		   )
		  )
		 )
	  )
	)
   
   (get-template-declaration typenames)

   (let ((line-length 0) (retprefix "") (symbol "") (argsuffix))

	 (setf namespace (get-namespace namespace))

	 ;; forms the type of return value.
	 (if (not (hryky-common::is-empty rettype))
		 (setf retprefix (editor::concat rettype " ")))

	 ;; forms the name of the symbol.
	 (setf symbol
		   (format nil "~A~A("
				   (get-namespace-prefix namespace) funcname))

	 ;; forms the artuments.
	 (setf argsuffix (format nil "~A)" args ))

	 ;; If the entire lengh is longer than the length of default columns.
	 (if (< *row-length-max* (length (editor::concat retprefix symbol argsuffix)))
		 ;; if the function has no argument
		 (if (hryky-common::is-empty args)
			 ;; inserts the RET between the type of return value and the symbol.
			 (setf retprefix (editor::concat retprefix "\n"))
		   ;; if the function has some arguments
		   (progn
			 ;; inserts the RET between the symbol and the head of arguments.
			 (setf argsuffix (editor::concat "\n\t" argsuffix))
			 ;; if the length of the sum of the symbol and the return value is 
			 ;; longer than the length of default columns.
			 (if (< *row-length-max* (length (editor::concat retprefix symbol)))
				 ;; inserts the RET between the return value and the symbol.
				 (setf retprefix (editor::concat retprefix "\n"))))))

	 (format nil "~A~A~A\n" retprefix symbol argsuffix)
	 )
   )
  )

;;--------------------------------------
;; retrieves the archetype of the member function of C++ class.
;;--------------------------------------
(defun get-cpp-memfunc
  (
   namespace 
   classname 
   funcname 
   desc 
   rettype 
   args
   typenames 
   &key
   ((:is-virtual is-virtual) nil)
   ((:is-static is-static) nil)
   ((:is-const is-const) nil)
   ((:is-prototype is-prototype) nil)
   )
  (editor::concat
   (get-cpp-memfunc-header
	namespace 
	classname 
	funcname 
	desc 
	rettype 
	args
	typenames 
	:is-virtual is-virtual 
	:is-static is-static 
	:is-const is-const
	:is-prototype is-prototype
	)
   (format nil "{\n~Areturn;\n}\n" (hryky-common::get-indent))))

;;--------------------------------------
;; retrieves the first part of the definition of the member function of C++ class
;;--------------------------------------
(defun get-cpp-memfunc-header
  (namespace
   classname
   funcname
   desc
   rettype
   args
   typenames
   &key
   ((:func-typenames func-typenames) "")
   ((:is-virtual is-virtual) nil)
   ((:is-static is-static) nil)
   ((:is-const is-const) nil)
   ((:is-prototype is-prototype) nil)
   )

  (let ((line-length 0) (retprefix "") (symbol "") (argsuffix))

	(setf namespace (get-namespace namespace))
	(setf classname (get-classname classname namespace))
	
	;; forms the part of the return value.
	(if (not (hryky-common::is-empty rettype))
		(setf retprefix (editor::concat rettype " ")))

	;; forms the part of the symbol.
	(setf
	 symbol
	 (format
	  nil
	  "~A::~A("
	  (get-template-classname namespace classname typenames)
	  funcname)
	 )

	;; forms the part of the arguments
	(setf
	 argsuffix
	 (format nil "~A)~A" args (if is-const " const" ""))
	 )

	;; if the entire length is longer than the length of default columns.
	(if (< *row-length-max* (length (editor::concat retprefix symbol argsuffix)))
		;; if this function has no arguments.
		(if (hryky-common::is-empty args)
			;; inserts the RET between the return value and the symbol.
			(setf retprefix (editor::concat retprefix "\n"))
		  ;; if this function has some arguments.
		  (progn
			;; inserts the RET between the symbol and the head of arguments.
			(setf argsuffix (editor::concat "\n\t" argsuffix))
			;; if the length of the sum of the return value and the symbol is longer
			;; than the length of default columns.
			(if (< *row-length-max* (length (editor::concat retprefix symbol)))
				;; inserts the RET between the return value and the symbol.
				(setf retprefix (editor::concat retprefix "\n"))
			  )
			)
		  )
	  )

	(editor::concat
	 ;; shapes the comment
	 (get-c-comment
	  desc
	  ;; appends the prototype declaration for the declaration of this class.
	  (if is-prototype
		  (hryky-common::add-indent
		   (editor::concat
			(get-prototype-desc desc)
			(format
			 nil "~A\n\n"
			 (get-prototype-function
			  funcname
			  rettype
			  args
			  :typenames func-typenames
			  :is-virtual is-virtual
			  :is-static is-static
			  :is-const is-const
			  )
			 )
			)
		   )
		)
	  )

	 ;; appends the first part of the definition of the member function.
	 (get-template-declaration typenames)
	 (get-template-declaration func-typenames)
	 (format nil "~A~A~A\n" retprefix symbol argsuffix)
	 )
	)
  )

;;--------------------------------------
;; retrieves the declaration of C language structure.
;;--------------------------------------
(defun get-c-struct
  (structname desc)
  (editor::concat
   (get-c-comment desc)
   (format nil "struct ~A\n{\n};\n" structname structname)
   (format nil "#ifndef __cplusplus\n")
   (format nil "typedef struct ~A ~A;\n" structname structname)
   (format nil "#endif\n")))

;;--------------------------------------
;; retrieves the declaration of C++ structure.
;;--------------------------------------
(defun get-cpp-struct
  (desc structname namespace)
  (setf namespace (get-namespace namespace))
  (editor::concat
   (get-c-comment
	desc
	(editor::concat
	 (format nil "\t/// ~A.\n\tstruct ~A;\n\n" desc structname)))
   (format
	nil "struct ~A~A\n{\n};\n"
	(get-namespace-prefix namespace) structname)
   ))

;;--------------------------------------
;; retrieves the declaration of C++ class
;;--------------------------------------
(defun get-cpp-class
  (
  args 
  namespace 
  classname 
  desc 
  typenames
  baseclass 
  &key
   ((:is-prototype is-prototype) nil)
   ((:is-instantiate is-instantiate) nil)
   ((:is-singleton is-singleton) nil)
   )

  ;; refines the namespace.
  (setf namespace (get-namespace namespace))
  ;; refines the name of class.
  (setf classname (get-classname classname namespace))
  
  (editor::concat
   ;; shapes the comment.
   (get-c-comment 
	desc
	;; appends the declaration of this class for forward reference.
	(if is-prototype
		(hryky-common::add-indent
		 (editor::concat
		  (get-prototype-desc desc)
		  ;;  For the assignment of default arguments, 
		  ;; class declaration can't use
		  ;; the macro for default template argument.
		  (get-template-declaration typenames)
		  (format nil "class ~A;\n\n" classname))
		 )
	  )
	)
	
   (get-template-declaration typenames)
   
   (format
	nil "class ~A~A~A\n{\n"
	(get-namespace-prefix namespace)
	classname
	(if (hryky-common::is-empty baseclass) ""
	  (editor::concat " :\n\tpublic " baseclass))
	)
   (format nil "public :\n\n")

   (hryky-common::add-indent
	(editor::concat

	 (if (not (hryky-common::is-empty baseclass))
		 (editor::concat
		  (format nil "typedef ~A base_type;\n\n" baseclass)
		  )
	   )

	 (format 
	  nil "typedef ~A this_type;\n\n" 
	  (get-default-template-classname "" classname typenames)
	  )

	 (if is-instantiate
		 (editor::concat
		  (format nil "/// instance type.\n")
		  (format nil "typedef this_type * instance_type;\n\n")

		  (format nil "/// create instance.\n")
		  (format nil "static instance_type instantiate(~A);\n\n" args)

		  (format nil "/// release instance.\n")
		  (format nil "~Avoid release();\n\n"
				  (if (hryky-common::is-empty baseclass) "" "virtual "))
		  )
	   )
	   
	 (format nil "/// default constructor.\n")
	 (format nil "~A();\n\n" classname)

	 (format nil "/// copy constructor.\n")
	 (format nil "~A(this_type const &);\n\n" classname)

	 (format nil "/// move constructor.\n")
	 (format nil "~A(this_type &&);\n\n" classname)

	 (if (not (hryky-common::is-empty args))
		 (editor::concat
		  (format nil "/// constructor.\n")
		  (format nil "~A(~A);\n\n" classname args))
	   )

	 (format nil "/// destructor.\n")
	 (format
	  nil "~A();\n\n"
	  (editor::concat "~~" classname))

	 (format nil "/// assignment operator.\n")
	 (format nil "hryky_assign_op;\n\n")

	 (format nil "/// move assignment operator.\n")
	 (format nil "hryky_move_assign_op;\n\n")

	 (format nil "/// releases the internal resources.\n")
	 (format nil "void clear();\n\n")

	 (format 
	  nil "/// interchanges the each internal resources of two instances.\n")
	 (format nil "void swap(this_type & src);\n\n")
	 
	 (format nil "/// outputs the information through stream.\n")
	 (format nil "template <typename StreamT>\n")
	 (format nil "StreamT & write_to(StreamT & out) const;\n\n")
	 
	 )
	)
	

   (format nil "protected :\n\n")

   (hryky-common::add-indent
	(editor::concat

	 (if is-instantiate
		 (editor::concat
		  (format nil "/// initialization.\n")
		  (format nil "bool initialize(~A);\n\n" args)
		  )
	   )
	  
	 )
	)

   (format nil "private :\n\n")

   (hryky-common::add-indent
	(editor::concat
	
	 ""
	 )
	)

   (format nil "};\n"))
  )
   
;;--------------------------------------
;; handling error
;;--------------------------------------
(defun get-error-declaration ()
  (editor::concat
   (format nil "/// error.\n")
   (format nil "struct Error\n")
   (format nil "{\n")
   (hryky-common::add-indent
	(editor::concat
	 (format nil "enum kind_type\n")
	 (format nil "{\n")
	 (hryky-common::add-indent
	  (editor::concat
	   (format nil "none,\n")
	   )
	  )
	 (format nil "};\n")
	 )
	)
   (format nil "};\n")
   (format nil "typedef Error::kind_type error_type;\n\n")
   (format nil "error_type error() const { return this->error_; }\n\n")
   )
  )

;;--------------------------------------
;; gets a definition of constructor
;;--------------------------------------
(defun get-cpp-constructor
  (namespace 
   classname 
   args 
   desc 
   typenames 
   baseclass
   &key
   ((:is-prototype is-prototype) nil)
   )
  (editor::concat
   (get-cpp-constructor-header
	namespace
	classname
	args
	desc
	typenames
	baseclass
	:is-prototype is-prototype)
   (format nil "{\n")
   (format nil "}\n")
   )
  )
  
;;--------------------------------------
;; gets a header of the definition of constructor
;;--------------------------------------
(defun get-cpp-constructor-header
  (namespace 
   classname 
   args 
   desc 
   typenames 
   baseclass
   &key
   ((:is-prototype is-prototype) nil)
   )
  (setf baseclass (get-baseclass baseclass))
  (setf namespace (get-namespace namespace))
  (setf classname (get-classname classname namespace))
  (editor::concat
   (get-cpp-memfunc-header
	namespace 
	classname 
	classname 
	desc 
	"" 
	args 
	typenames 
	:is-prototype is-prototype
	)
   (hryky-common::add-indent
	(if (hryky-common::is-empty baseclass)
		""
	  (editor::concat
	   (format nil ": ~A()\n" baseclass)
	   )
	  )
	)
   )
  )
  
;;--------------------------------------
;; gets a definition of default constructor
;;--------------------------------------
(defun get-cpp-default-constructor
  (namespace
   classname
   typenames
   baseclass
   &key
   ((:is-prototype is-prototype) nil)
   )
  (get-cpp-constructor
   namespace 
   classname 
   "" 
   "default constructor" 
   typenames 
   baseclass 
   :is-prototype is-prototype)
  )
;;--------------------------------------
;; gets a definition of copy constructor
;;--------------------------------------
(defun get-cpp-copy-constructor
  (namespace
   classname
   typenames
   baseclass
   &key
   ((:is-prototype is-prototype) nil)
   )
  (editor::concat
   (get-cpp-constructor-header
	namespace
	classname
	"this_type const & rhs"
	"copy constructor"
	typenames
	""
	:is-prototype is-prototype
	)
   (hryky-common::add-indent
	(if (hryky-common::is-empty baseclass)
		""
	  (editor::concat
	   (format nil ": ~A(rhs)\n" baseclass)
	   )
	  )
	)
   (format nil "{\n")
   (format nil "}\n")
   )
  )  
;;--------------------------------------
;; gets a definition of move constructor
;;--------------------------------------
(defun get-cpp-move-constructor
  (namespace
   classname
   typenames
   baseclass
   &key
   ((:is-prototype is-prototype) nil)
   )
  (editor::concat
   (get-cpp-constructor-header
	namespace
	classname
	"this_type && rhs"
	"move constructor"
	typenames
	""
	:is-prototype is-prototype)
   (hryky-common::add-indent
	(if (hryky-common::is-empty baseclass)
		""
	  (editor::concat
	   (format nil ": ~A(std::move(rhs))\n" baseclass)
	   )
	  )
	)
   (format nil "{\n")
   (format nil "}\n")
   )
  )
  
;;--------------------------------------
;; gets a definition of destructor
;;--------------------------------------
(defun get-cpp-destructor
  (namespace
   classname
   typenames
   &key
   ((:is-prototype is-prototype) nil)
   ((:is-signleton is-singleton) nil)
   )
  (setf namespace (get-namespace namespace))
  (setf classname (get-classname classname namespace))
  (editor::concat
   (get-cpp-memfunc-header
	namespace
	classname
	(editor::concat "~~" classname)
	"destructor"
	""
	""
	typenames
	:is-prototype is-prototype)
   (format nil "{\n")
   (hryky-common::add-indent
	(editor::concat
	 (if is-singleton
		 (format nil "g_instance = 0;\n") "")
	 )
	)
   (format nil "}\n")
   )
  )
  
;;--------------------------------------
;; gets a definition of clearing the internal resources.
;;--------------------------------------
(defun get-cpp-clear
  (namespace
   classname
   typenames
   baseclass
   &key
   ((:is-prototype is-prototype) nil)
  )
  (setf baseclass (get-baseclass baseclass))
  (setf namespace (get-namespace namespace))
  (setf classname (get-classname classname namespace))
  (editor::concat
   (get-cpp-memfunc-header
	namespace 
	classname 
	"clear"
	"releases the internal resources" 
	"void"
	""
	typenames 
	:is-prototype is-prototype
	)
   (format nil "{\n")
   (hryky-common::add-indent
	(editor::concat
	 (if (hryky-common::is-empty baseclass) ""
	   (format nil "this->~A::clear();\n" baseclass)
	   )
	 )
	)
   (format nil "}\n")
   )
  )
  
;;--------------------------------------
;; gets a definition of assignment operator
;;--------------------------------------
(defun get-cpp-assignment-operator
  (namespace
   classname
   typenames
   &key
   ((:is-prototype is-prototype) nil)
  )
  (setf namespace (get-namespace namespace))
  (setf classname (get-classname classname namespace))
  (editor::concat
   (get-cpp-memfunc-header
	namespace 
	classname 
	"operator="
	"assignment operator" 
	(format 
	 nil "~A &"
	 (get-template-classname namespace classname typenames))
	"this_type const & rhs"
	typenames 
	:is-prototype is-prototype
	)
   (format nil "{\n")
   (hryky-common::add-indent
	(editor::concat
	 "if (this == &rhs) { return *this; }\n\n"
	 "this_type(rhs).swap(*this);\n\n"
	 "return *this;\n"
	 )
	)
   (format nil "}\n")
   )
  )
  
;;--------------------------------------
;; gets a definition of swap
;;--------------------------------------
(defun get-cpp-swap
  (namespace
   classname
   typenames
   baseclass
   &key
   ((:is-prototype is-prototype) nil)
  )
  (setf baseclass (get-baseclass baseclass))
  (setf namespace (get-namespace namespace))
  (setf classname (get-classname classname namespace))
  (editor::concat
   (get-cpp-memfunc-header
	namespace 
	classname 
	"swap"
	"interchanges the each internal resources of two instances" 
	"void"
	"this_type & src"
	typenames 
	:is-prototype is-prototype
	)
   (format nil "{\n")
   (hryky-common::add-indent
	(editor::concat
	 (if (hryky-common::is-empty baseclass) ""
	   (format nil "this->~A::swap(src);\n" baseclass)
	   )
	 )
	)
   (format nil "}\n")
   )
  )
  
;;--------------------------------------
;; gets a definition of write_to
;;--------------------------------------
(defun get-cpp-write-to
  (namespace 
   classname 
   typenames
   baseclass
   &key
   ((:is-prototype is-prototype) nil)
   )
  (setf baseclass (get-baseclass baseclass))
  (setf namespace (get-namespace namespace))
  (setf classname (get-classname classname namespace))
  (editor::concat
   (get-cpp-memfunc-header
	namespace 
	classname 
	"write_to"
	"outputs the information through stream" 
	"StreamT &"
	"StreamT & out"
	typenames 
	:func-typenames "typename StreamT"
	:is-const t
	:is-prototype is-prototype
	)
   (format nil "{\n")
   (hryky-common::add-indent
	(editor::concat
	 "stream::map::Scope<StreamT> const map(out);\n"
	 (if (hryky-common::is-empty baseclass) ""
	   (format 
	   nil 
		"out << stream::denote(\"~A\") << *static_cast<~A const *>(this);\n" 
		baseclass baseclass)
	   )
	 "return out;\n"
	 )
	)
   (format nil "}\n")
   )
  )
  
;;--------------------------------------
;; gets a definition of swap as no-member function
;;--------------------------------------
(defun get-cpp-swapfunc
  (namespace 
   classname 
   typenames
   &key
   ((:is-prototype is-prototype) nil)
   )
  (setf namespace (get-namespace namespace))
  (setf classname (get-classname classname namespace))
  (editor::concat
   (get-cpp-func-header
	namespace 
	"swap"
	"interchanges two instances of the same type" 
	"void"
	(format 
	 nil "~A & lhs, ~A & rhs" 
	 (get-template-classname "" classname typenames)
	 (get-template-classname "" classname typenames)
	 )
	typenames 
	:is-prototype is-prototype
	)
   (format nil "{\n")
   (hryky-common::add-indent "lhs.swap(rhs);\n")
   (format nil "}\n")
   )
  )
  
;;--------------------------------------
;; retrieves the declaration of template parameters.
;;--------------------------------------
(defun get-template-declaration
  (typenames)
  (if (hryky-common::is-empty typenames)
	  ""
	(format nil "template <~A>\n" (get-template-declaration-entity typenames))
	)
  )
  
;;--------------------------------------
;; generates the default declaration of template parameters if the typename is specified.
;;--------------------------------------
(defun get-default-template-declaration
  (typenames)
  (if (hryky-common::is-empty typenames)
	  ""
	(format nil "template <~A>\n" *default-template-param*)
	)
  )
  
;;--------------------------------------
;; generates the template parameters.
;;--------------------------------------
(defun get-template-declaration-entity
  (typenames)
  (if (is-default-template-specifier typenames) 
	  *default-template-param* 
	typenames)
  )

;;--------------------------------------
;; retrieves the list of the template arguments.
;;--------------------------------------
(defun get-template-arguments
  (typenames)
  (if (hryky-common::is-empty typenames)
	  ""
	(format nil "<~A>" (get-template-arguments-entity typenames))
	)
  )
  
;;--------------------------------------
;; generates the default template arguments if the typename is specified.
;;--------------------------------------
(defun get-default-template-arguments
  (typenames)
  (if (hryky-common::is-empty typenames)
	  ""
	(format nil "<~A>" *default-template-arg*)
	)
  )
  
;;--------------------------------------
;; creates the template arguments from the declaration of parameters
;;--------------------------------------
(defun get-template-arguments-entity
  (typenames)
  (if (is-default-template-specifier typenames)
	  *default-template-arg*
	(hryky-common::join
	 (labels
		 ((seconds (src)
			(if (< 2 (length src))
				(cons (second src) (seconds (rest (rest src))))
			  (if (= 2 (length src))
				  (list (second src))
				(if (= 1 (length src))
					(list (first src))
				  (list "")
				  )
				)
			  )
			))
	   (seconds (editor::split-string typenames " ," nil))
	   )
	 ", "
	 )
	)
  )
  
;;--------------------------------------
;; confirms whether the template parameter is default.
;;--------------------------------------
(defun is-default-template-specifier
  (typenames)
  (string-equal typenames *default-template-specifier*)
  )

;;--------------------------------------
;; retrieves the brief comment for prototype.
;;--------------------------------------
(defun get-prototype-desc
  (&optional (desc ""))
  (format nil "/// ~A.\n" desc))
  
;;--------------------------------------
;; retrieves the prototype declaration.
;;--------------------------------------
(defun get-prototype-function
  (
   funcname rettype args
   &optional
   &key
   ((:typenames typenames) "")
   ((:is-virtual is-virtual) nil)
   ((:is-static is-static) nil)
   ((:is-const is-const) nil)
   )
  (let ((rettype-section ""))
	(if (not (hryky-common::is-empty rettype))
		(setf rettype-section (editor::concat rettype " ")))
	(editor::concat
	 (get-template-declaration typenames)
	 (format
	  nil
	  "~A~A~A~A\(~A\)~A;"
	  (if is-virtual "virtual " "")
	  (if is-static "static " "")
	  ;; removes the namespace from the type of the return value.
	  (ignore-namespace-prefix rettype-section "")
	  funcname
	  args
	  (if is-const " const" "")
	  )
	 )
	)
  )

;;--------------------------------------
;; refines the namespace.
;;--------------------------------------
(defun get-namespace
  (&optional (namespace ""))
  (string-trim
   " "
   (if (hryky-common::is-empty namespace)
	   (get-namespace-from-path "")
	 namespace))
  )

;;--------------------------------------
;; retrieves the namespace as the prefix of the symbol.
;;--------------------------------------
(defun get-namespace-prefix
  (namespace)
  (if (hryky-common::is-empty namespace)
	  "" (editor::concat namespace "::")))

;;--------------------------------------
;; retrieves the definition of the namespace.
;;--------------------------------------
(defun get-namespace-definition
  (namespace &optional (desc ""))
  (get-namespace-definition-from-list
   (if (hryky-common::is-empty namespace)
	   (cons (string "") '())
	 (editor::split-string namespace #\:))
   desc)
  )

;;--------------------------------------
;; removes the prefix of namespace from the symbol.
;;--------------------------------------
(defun ignore-namespace-prefix
  (string &optional (prefix ""))
  (setf prefix (get-namespace prefix))
  (editor::substitute-string
   string
   (format nil "^~A::" prefix) "" :case-fold t))

;;--------------------------------------
;; retrieves the definition of the namespace from the list of the namespace elements.
;;--------------------------------------
(defun get-namespace-definition-from-list
  (namespace-list desc)
  (if namespace-list
	  (let ((namespace (car namespace-list)))
		(editor::concat
		 (format
		  nil "~A\n{\n"
		  (get-namespace-definition-line namespace))
		 (get-namespace-definition-from-list (cdr namespace-list) desc)
		 (format
		  nil "} // ~A\n"
		  (get-namespace-definition-line 
		   (if (hryky-common::is-empty namespace) "\"anonymous\"" namespace)
		   )
		  )
		 )
		)
	(format nil desc))
  )

;;--------------------------------------
;; removes the invalid namespace from the list of the namespace elements.
;;--------------------------------------
(defun remove-invalid-last-namespace
  (namespace-list)
  (if (and namespace-list (not (equal 0 (length namespace-list))))
	  (if (string-equal (first (last namespace-list)) "impl")
		  (hryky-common::pop-back namespace-list)
		namespace-list
		)
	namespace-list
	)
  )

;;--------------------------------------
;; retrieves the part of the definition of the namespace element.
;;--------------------------------------
(defun get-namespace-definition-line
  (namespace)
  (format
   nil "namespace~A"
   (if (or (not namespace) (hryky-common::is-empty namespace)) "" (editor::concat " " namespace)
	 )
   )
  )

;;--------------------------------------
;; generates the fullname of class with default template arguments.
;;--------------------------------------
(defun get-default-template-classname
  (namespace classname typenames)
  (get-template-classname 
   namespace 
   classname 
   (if (hryky-common::is-empty typenames) typenames "*")
   )
  )
;;--------------------------------------
;; retrieves the name of class with template arguments.
;;--------------------------------------
(defun get-template-classname
  (namespace classname typenames)
  (editor::concat
   (get-namespace-prefix namespace)
   classname
   (get-template-arguments typenames)
   ))

;;--------------------------------------
;; retrieves the name of the pointer of class with template arguments.
;;--------------------------------------
(defun get-template-classname-ptr
  (namespace classname typenames)
  (editor::concat (get-template-classname namespace classname typenames) " *"))
  
;;--------------------------------------
;; retrieves the function for instantiation.
;;--------------------------------------
(defun get-cpp-instantiate
  (
   namespace
   classname
   args
   typenames
   &key
   ((:is-prototype is-prototype) nil)
   ((:is-singleton is-singleton) nil)
   )
   
  (setf namespace (get-namespace namespace))
  (setf classname (get-classname classname namespace))
  (editor::concat
   (get-cpp-memfunc-header
	namespace 
	classname 
	"instantiate" 
	"create and initialize an instance"
	(format
	 nil "~A::instance_type"
	 (get-template-classname namespace classname typenames))
	args
	typenames 
	:is-static t
	:is-prototype is-prototype
	)

   (format nil "{\n")
   (hryky-common::add-indent
	(editor::concat
	 (if is-singleton
		 (editor::concat
		  (format nil "// check existing instance.\n")
		  (format nil "if (0 != g_instance)\n")
		  (hryky-common::add-indent
		   (editor::concat
			(format nil "return g_instance;\n\n")
			)
		   )
		  )
	   )
	   
	 (format nil "// allocate.\n")
	 (format nil "instance_type instance = reinterpret_cast<instance_type>(\n")
	 (hryky-common::add-indent
	  (format nil "::operator new(sizeof(this_type)));\n\n"))
	  
	 (format nil "if (0 == instance) return 0;\n\n")

	 (format nil "// create instance.\n")
	 (format nil "instance = new (instance) this_type(~A);\n\n" (remove-type args))
	 (if is-singleton
		 (format nil "g_instance = instance.get();\n\n"))
	 (format nil "// initialize the instance.\n")
	 (format nil "if (!instance->initialize(~A))\n" (remove-type args))
	 (format nil "{\n")
	 (hryky-common::add-indent (editor::concat (format nil "return 0;\n")))
	 (format nil "}\n\n")
	 (format nil "return instance;\n")))
   (format nil "}\n")
   )
  )
  
;;--------------------------------------
;; retrieves the function to release the instance.
;;--------------------------------------
(defun get-cpp-release
  (namespace classname baseclass)
  (setf namespace (get-namespace namespace))
  (setf classname (get-classname classname namespace))
  (editor::concat 
   (get-cpp-memfunc-header
	namespace 
	classname 
	"release" 
	"release instance" 
	"void" 
	"" 
	"" 
	)
   (format nil "{\n")
   (hryky-common::add-indent
	(editor::concat
	 (format nil "this->~A~A();\n" "~~" classname)
	 (format nil "::operator delete(this);\n")
	 ))
   (format nil "}\n")
   ))
   
;;--------------------------------------
;; retrieves the declaration of the initializer of the instance.
;;--------------------------------------
(defun get-cpp-initializer()
  (hryky-common::add-indent
   (editor::concat
	(format nil "/// initializer.\n")
	(format nil "struct Initializer : Noncopyable\n")
	(format nil "{\n")
	(hryky-common::add-indent
	 (editor::concat
	  (format nil "Initializer() {}\n")))
	(format nil "};\n\n"))))
	
;;--------------------------------------
;; retrieves the function to initialize the instance.
;;--------------------------------------
(defun get-cpp-initialize
  (args namespace classname typenames baseclass)
  (setf baseclass (get-baseclass baseclass))
  (editor::concat
   (get-cpp-memfunc-header
	namespace 
	classname 
	"initialize" 
	"initialize the instance" 
	"bool" 
	args
	typenames 
	)
   (format nil "{\n")
   (hryky-common::add-indent
	(editor::concat
	 (if (hryky-common::is-empty baseclass)
		 ""
	   (editor::concat
		(format nil "if (!this->~A::initialize())\n" baseclass)
		(format nil "{\n")
		(hryky-common::add-indent
		 (editor::concat
		  (format nil "return false;\n")
		  )
		 )
		(format nil "}\n")
		)
	   )
	 (format nil "return true;\n")
	 ))
   (format nil "}\n")
   )
  )
  
;;--------------------------------------
;; retrieves the declaration of the parameter to reset an instance.
;;--------------------------------------
(defun get-cpp-reset-parameter()
  (hryky-common::add-indent
   (editor::concat
	(format nil "/// parameters for reset().\n")
	(format nil "struct ResetParameter\n")
	(format nil "{\n")
	(hryky-common::add-indent
	 (editor::concat
	  (format nil "ResetParameter() {}\n")))
	(format nil "};\n\n"))))
	
;;--------------------------------------
;; retrieves the function to reset the instance.
;;--------------------------------------
(defun get-cpp-reset
  (args namespace classname typenames baseclass)
  ;; refines the base class.
  (setf baseclass (get-baseclass baseclass))
  
  (editor::concat
   (get-cpp-memfunc-header
	namespace 
	classname 
	"initialize" 
	"initialize the instance" 
	"bool" 
	args
	typenames 
	)
   (format nil "{\n")
   (hryky-common::add-indent
	(editor::concat
	 (if (hryky-common::is-empty baseclass)
		 ""
	   (editor::concat
		(format nil "if (!this->~A::reset()) { return false; }\n" baseclass)
		)
	   )
	 (format nil "return true;\n")
	 ))
   (format nil "}\n")
   )
  )
  
;;--------------------------------------
;; retrieves the name of the header corresponding to the source.
;;--------------------------------------
(defun get-cpp-header-filename
  (&optional 
   (basename 
	(hryky-common::get-file-base-name 
	 (hryky-common::get-selected-path))))
  (format
   nil "~A/~A.h"
   ;;    (first
   ;; 	(editor::split-string basename #\_))
   "."
   basename)
  )
  
;;--------------------------------------
;; retrieves the include directive of the header corresponding to the source.
;;--------------------------------------
(defun get-cpp-header-include
  ()
  (get-cpp-include (get-cpp-header-filename)))
  
;;--------------------------------------
;; retrieves the include directive of the precompiled header.
;;--------------------------------------
(defun get-cpp-precompile-include
  ()
  (get-cpp-include *precompiled-header*)
  )
;;--------------------------------------
;; retrieves the include directive.
;;--------------------------------------
(defun get-cpp-include
  (path)
  (format nil "#include \"~A\"\n" path))

;;--------------------------------------
;; retrieves the include-guard of C/C++
;;--------------------------------------
(defun get-include-guard
  ()
  ;; replaces characters to '_' except for acceptable characters of macro.
  (replace-to-c-identifier
   (format
	nil "~:@(~A~A~)"
	(editor::substitute-string (hryky-common::get-file-name) "[^0-9a-zA-Z_]" "_")
	(editor::format-date-string "_%Y%m%d%H%M%S%i"))))

;;--------------------------------------
;; retrieves the C/C++ comment line to divide region explicitly.
;;--------------------------------------
(defun get-c-comment-division
  (&optional (division 78))
  (format nil "//~A\n" (hryky-common::get-chars #\- division)))

;;--------------------------------------
;; retrieves the C/C++ comment lines
;;--------------------------------------
(defun get-c-comment-block
  (desc)
  (editor::concat
   (get-c-comment-division)
   (format nil "// ~A\n" desc)
   (get-c-comment-division)))
   
;;--------------------------------------
;; removes types from the parameters
;;--------------------------------------
(defun remove-type
  (args)
  (or
   (let ((result nil))
	 (dolist
		 (item
		  ;; splits the parameters by comma.
		  (editor::split-string args #\, nil " ")
		  ;; concatenates each element of the list with comma.
		  (hryky-common::join
		   ;; reverses the order of the list.
		   (reverse result) ", ")
		  )
	   (push
		;; removes the types by regular expression.
		(editor::substitute-string item ".* [\*\&]*" "")
		result)
	   )
	 )
   "")
  )
  
;;--------------------------------------
;; adjusts the string to the acceptable characters for C language symbol.
;;--------------------------------------
(defun replace-to-c-identifier
  (string &optional (dest_char #\_))
  (when string
	;; replaces characters to dest_char except for the acceptable character for C language symbol.
	(substitute-if
	 dest_char
	 ;; predicate
	 #'(lambda (character)
		 (or
		  (equal character #\_)
		  (equal character #\-)
		  (equal character #\.)
		  (equal character #\:)
		  (equal character #\/)
		  (equal character (hryky-common::get-white-space))))
	 string)))
  
;;------------------------------------------------------------------------------
;; inserts archetypes for Ruby
;;------------------------------------------------------------------------------

;;--------------------------------------
;; retrieves the definition of Ruby class.
;;--------------------------------------
(defun get-ruby-class
  (name desc)
  (editor::concat
   (get-ruby-comment-division-begin 64)
   (format nil "=== ~A\n" classname)
   (format nil "    ~A\n" desc)
   (get-ruby-comment-division-end 64)
   (format nil "class ~A\n\n" classname)
   (get-ruby-method "initialize" "initialization")
   (format nil "end\n" classname)
   )
  )

;;--------------------------------------
;; retrieves the definition of Ruby method.
;;--------------------------------------
(defun get-ruby-method
  (name desc)
  (editor::concat
   (get-ruby-comment-division-begin 32)
   (format nil "--- ~A\n" name)
   (format nil "    ~A\n" desc)
   (get-ruby-comment-division-end 32)
   (format nil "~Adef ~A()\n" (get-ruby-indent) name)
   (format nil "~Aend\n" (get-ruby-indent) name)
   )
  )

;;--------------------------------------
;; retrieves the archetype of Ruby source.
;;--------------------------------------
(defun get-ruby-source
  (desc)
  (editor::concat
   (get-ruby-comment-division-begin 64)
   (format nil "= ~A\n\n" (hryky-common::get-file-name))
   (format nil "== brief\n~A\n\n" desc)
   (format nil "== author\n~A\n\n" hryky-common::*author-name*)
   (format nil "== version\n$~A$\n\n" "Id")
   (get-ruby-comment-division-end 64)

   (format nil "\n")

   (get-ruby-comment-division-begin 64)
   (format nil "== class definition\n")
   (get-ruby-comment-division-end 64)

   (format nil "\n")

   (get-ruby-comment-division-begin 64)
   (format nil "== method definition\n")
   (get-ruby-comment-division-end 64)

   (format nil "\n")

   (get-ruby-comment-division-begin 64)
   (format nil "== execution\n")
   (get-ruby-comment-division-end 64)

   (format nil "if File.expand_path($0) == File.expand_path(__FILE__)\n\n")
   (format nil "end\n")
   )
  )

;;--------------------------------------
;; retrieves the first part of Ruby embedded document.
;;--------------------------------------
(defun get-ruby-comment-division-begin
  (length)
  (format nil "#~A\n=begin\n" (hryky-common::get-chars #\- length))
  )

;;--------------------------------------
;; retrieves the last part of Ruby embedded document.
;;--------------------------------------
(defun get-ruby-comment-division-end
  (length)
  (format nil "=end\n#~A\n" (hryky-common::get-chars #\- length))
  )

;;--------------------------------------
;; retrieves the indet character of Ruby.
;;--------------------------------------
(defun get-ruby-indent()
  (hryky-common::get-chars #\  editor::*ruby-indent-column*))

;;--------------------------------------
;; encloses the word under the current position as C/C++ comment
;;--------------------------------------
(defun enclose-as-comment-c
  (&optional (begin (editor::region-beginning)) (end (editor::region-end)))
  (editor::save-excursion
	(editor::goto-char end)
	(editor::with-output-to-selected-buffer (format t " */"))
	(editor::goto-char begin)
	(editor::with-output-to-selected-buffer (format t "/* "))
	)
  )
