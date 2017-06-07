"-------------------------------------------------------------------------------
"functions used in this script
"-------------------------------------------------------------------------------
"retrieves the EOL format of the current file.
function! s:EolFormat()
	return &fileformat
endfunction

"retrieves the character encoding of the current file.
function! s:Encoding()
	let enc = &fileencoding
	let enc = empty(l:enc) ? &encoding : l:enc
	return l:enc . (&l:bomb ? '+BOM' : '')
endfunction

"retrieves the current date as string.
function! s:Date(...)
	return strftime('%Y-%m-%d', 0 <# a:0 ? a:1 : localtime())
endfunction

"retrieves the current time as string.
function! s:Time(...)
	return strftime('%H:%M:%S', 0 <# a:0 ? a:1 : localtime())
endfunction

"retrieves the current date and time as string.
function! s:DateTime(...)
	let time = 0 <# a:0 ? a:1 : localtime()
	return s:Date(l:time) . 'T' . s:Time(l:time)
endfunction

"retrieves a comment line as a border.
function! s:CommentBorder()
	return '//' . repeat('-', 78)
endfunction

"call input() conservatively.
function! s:Input(...)
	let args = 0 <# a:0 ? a:1 : {}
	let prompt = s:DictValue(args, 'prompt', 'input: ')
	let defvalue = s:DictValue(args, 'defvalue')
	let completion = s:DictValue(args, 'completion')
	call inputsave()
	if empty(l:completion)
		let input = input(l:prompt, l:defvalue)
	else
		let input = input(l:prompt, l:defvalue, l:completion)
	endif
	call inputrestore()
	return l:input
endfunction

"retrieves the definition of C++ namespace.
function! s:DefNamespace(...)
	let str = 0 <# a:0 ? a:1 : s:Input(
		\ {'completion': 'cscope'
		\ ,'defvalue': s:NamespaceFrom()
		\ })
	let namespaces = split(l:str, ':\+')
	let ret = ''
	for namespace in l:namespaces
		if s:Anonymous() is# l:namespace
			let namespace = ''
		else
			let namespace = ' ' . l:namespace
		endif
		let ret .= 'namespace' . l:namespace . "\<CR>{\<CR>"
	endfor
	for namespace in reverse(l:namespaces)
		if s:Anonymous() is# l:namespace
			let namespace = ''
		else
			let namespace = ' ' . l:namespace
		endif
		let ret .= '}// namespace' . l:namespace . "\<CR>"
	endfor
	return l:ret
endfunction

"retrieves comment lines as a headline.
function! s:CommentHeadline(...)
	let str = 0 <# a:0 ? a:1 : s:Input()
	return s:Line(s:CommentBorder())
		\. s:Line('// ' . l:str)
		\. s:Line(s:CommentBorder())
endfunction

"retrieves an Include Guard used as a macro.
function! s:IncludeGuard(...)
	let name = 0 <# a:0 ? a:1 : expand('%:t') . s:DateTime()
	return toupper(
		\substitute(
			\substitute(l:name , '\W', '_', 'g'),
			\'_\+', '_', 'g'))
endfunction

"retrieves the argument from the dictionary.
function! s:Arg(dict, key, ...)
	let options = 0 <# a:0 ? a:1 : {}
	if !has_key(options, 'prompt')
		let options = copy(options)
		let options['prompt'] = a:key . ' is: '
	endif
	let ret = has_key(a:dict, a:key) ? a:dict[a:key] : s:Input(l:options)
	return l:ret
endfunction

"retrieves the value from the dictionary without prompt.
function! s:DictValue(dict, key, ...)
	let fallback = 0 <# a:0 ? a:1 : ''
	return has_key(a:dict, a:key) ? a:dict[a:key] : l:fallback
endfunction

"retrieves a line.
function! s:Line(...)
	let str = 0 <# a:0 ? a:1 : ''
	return empty(l:str) ?  '' : l:str . "\n"
endfunction

"retrieves a linebreak.
function! s:Newline()
	return "\n"
endfunction

"retrieves the indented lines.
function! s:Indent(...)
	let lines = 0 <# a:0 ? a:1 : ''
	let prefix = 1 <# a:0 ? a:2 : "\t"
	let desc = substitute(
		\ l:lines, '^\([^\n]\)', l:prefix . '\1', '')
	let desc = substitute(
		\ l:desc, '\n\([^\n]\)', "\n" . l:prefix . '\1', 'g')
	return l:desc
endfunction

"retrieves a block comment
function! s:CommentBlock(...)
	let desc = 0 <# a:0 ? a:1 : s:Input()
	let ret =
		\s:Line('/**')
		\. s:Indent(desc, '  ')
		\. (l:desc !~# '\n$' ? s:Newline() : '')
		\. s:Line(' */')
	return l:ret
endfunction

"concatenate two strings with a delimiter.
function! s:Concat(prefix, src, ...)
	let delimiter = 0 <# a:0 ? a:1 : ''
	if 0 <# strlen(a:prefix)
		if 0 <# strlen(a:src)
			return a:prefix . l:delimiter . a:src
		else
			return a:prefix
		endif
	elseif 0 <# strlen(a:src)
		return a:src
	else
		return ''
	endif
endfunction

"qualifies a name with the namespace.
function! s:Qualify(prefix, name)
	return s:Concat(a:prefix, a:name, '::')
endfunction

"constructs a namespace from strings.
function! s:JoinNamespace(...)
	let list = 0 <# a:0 ? a:1 : []
	return join(l:list, '::')
endfunction

"assigns the default prefix of namespace.
function! s:DefaultNamespace(...)
	let g:my.namespace = 0 <# a:0 ? a:1 : s:Input(
		\{'prompt': 'default namespace is : '
		\, 'defvalue': g:my.namespace
		\, 'completion': 'cscope'
		\})
endfunction

"assigns the default template parameters.
function! s:DefaultTemplateParams(...)
	let g:my.template_params = 0 <# a:0 ? a:1 : s:Input(
		\{'prompt': 'macro for template parameters is : '
		\, 'defvalue': g:my.template_params
		\, 'completion': 'cscope'
		\})
endfunction

"assigns the default template arguments.
function! s:DefaultTemplateArgs(...)
	let g:my.template_args = 0 <# a:0 ? a:1 : s:Input(
		\{'prompt': 'macro for template arguments is : '
		\, 'defvalue': g:my.template_args
		\, 'completion': 'cscope'
		\})
endfunction

"constructs template parameters from a string.
function! s:TemplateParamsFrom(...)
	let str = 0 <# a:0 ? a:1 : ''
	if empty(l:str)
		return ''
	endif
	let ret = l:str is# s:Anonymous() ? g:my.template_params : l:str
	return l:ret
endfunction

"retrieves template specifier.
function! s:SpecifyTemplateParams(str)
	let params = s:TemplateParamsFrom(a:str)
	return empty(l:params) ? '' : 'template <' . l:params . ' >'
endfunction

"specifies template arguments of class.
function! s:SpecifyTemplateArgs(cls, str)
	let args = s:TemplateArgsFrom(a:str)
	return empty(l:args) ? a:cls : a:cls . '<' . l:args . ' >'
endfunction

"constructs template arguments from a string.
function! s:TemplateArgsFrom(...)
	let str = 0 <# a:0 ? a:1 : ''
	if empty(l:str)
		return ''
	endif
	if l:str is# s:Anonymous()
		return g:my.template_args
	endif
	let params = split(str, '\s*,\s*')
	let args = []
	for param in l:params
		call add(l:args, split(param, '\s\+')[-1])
	endfor
	return join(args, ', ')
endfunction

"retrieves the secifier of anonymous namespace.
function! s:Anonymous()
	return '*'
endfunction

"retrieves the filename of the current buffer with extension.
function! s:Basename()
	return expand('%:t')
endfunction

"retrieves the filename of the current buffer without extension.
function! s:Filename()
	return expand('%:t:r')
endfunction

"constructs namespace components from a string.
function! s:ComponentsFrom(...)
	let str = s:Qualify(
		\g:my.namespace
		\, 0 <# a:0 ? a:1 : s:Filename())
	let components = tolower(
		\substitute(
			\substitute(l:str, '\(\u\+\)', ' \1', 'g')
			\, '[_:]\+\|\W\+', ' ', 'g'))
	let ret = split(components, '\s\+')
	if !empty(l:ret)
		let ret[-1] = toupper(strpart(l:ret[-1], 0, 1))
			\. strpart(l:ret[-1], 1)
	endif
	return l:ret
endfunc

"constructs a namespace from a string.
function! s:NamespaceFrom(...)
	let str = 0 <# a:0 ? a:1 : s:Filename()
	let components = s:ComponentsFrom(l:str)
	if !empty(l:components)
		let components = l:components[:-2]
	endif
	let ret = s:JoinNamespace(l:components)
	return l:ret
endfunction

"constructs a name of class from a string
function! s:ClsnameFrom(...)
	let str = 0 <# a:0 ? a:1 : s:Filename()
	let components = s:ComponentsFrom(l:str)
	return empty(l:components) ? '' : l:components[-1]
endfunction


"confirms whether a string is yes.
function! s:IsYes(...)
	return 0 <# a:0 ? (a:1 is# 'y') || (a:1 is# 1) : 0
endfunction

"retrieves a string if true.
function! s:Fallback(boolean, true, ...)
	let false = 0 <# a:0 ? a:1 : ''
	return a:boolean ? a:true : l:false
endfunction

"retrieves the declaration of a member function.
function! s:DeclMemfunc(...)
	let args = 0 <# a:0 ? a:1 : {}
	let completion = {'completion': 'cscope'}
	let funcname = s:Arg(l:args, 'funcname', l:completion)
	let funcargs = s:Arg(l:args, 'funcargs', l:completion)
	let rettype = s:Arg(l:args, 'rettype', l:completion)
	let tplparams = s:Arg(l:args, 'tplparams', completion)
	let is_static = s:IsYes(s:Arg(l:args, 'is_static'))
	let is_const = !is_static && s:IsYes(s:Arg(l:args, 'is_const'))
	let is_virtual = !is_static && s:IsYes(s:Arg(l:args, 'is_virtual'))
	let brief = s:Arg(l:args, 'brief')
	let ret = s:Line('/// ' . l:brief)
		\ . s:Line(s:SpecifyTemplateParams(l:tplparams))
		\ . s:Line(
			\ s:Fallback(l:is_static, 'static ')
			\ . s:Fallback(l:is_virtual, 'virtual ')
			\ . (empty(l:rettype) ? '' : l:rettype . ' ')
			\ . l:funcname . '(' . l:funcargs . ')'
			\ . s:Fallback(l:is_const, ' const')
			\ . ';')
		\ . s:Newline()
	return l:ret
endfunction

"retrieves the definition of a member function.
function! s:DefMemfunc(...)
	let args = 0 <# a:0 ? a:1 : {}
	let brief = s:Arg(l:args, 'brief')
	let namespace = s:NamespaceArg(l:args)
	let clsname = s:ClsnameArg(l:args)
	let completion = {'completion': 'cscope'}
	let funcname = s:Arg(l:args, 'funcname', l:completion)
	let funcargs = s:Arg(l:args, 'funcargs', l:completion)
	let rettype = s:Arg(l:args, 'rettype', l:completion)
	let cls_tplparams = s:Arg(l:args, 'cls_tplparams', l:completion)
	let func_tplparams = s:Arg(l:args, 'func_tplparams', l:completion)
	let is_static = s:IsYes(s:Arg(l:args, 'is_static'))
	let is_const = !is_static && s:IsYes(s:Arg(l:args, 'is_const'))
	let is_virtual = !is_static && s:IsYes(s:Arg(l:args, 'is_virtual'))
	let with_decl = s:IsYes(s:DictValue(l:args, 'with_decl', 'y'))
	let prototype = s:Fallback(with_decl, s:DeclMemfunc(
		\ { 'brief': l:brief
		\ , 'funcname': l:funcname
		\ , 'funcargs': l:funcargs
		\ , 'rettype': l:rettype
		\ , 'tplparams': l:func_tplparams
		\ , 'is_static': l:is_static
		\ , 'is_const': l:is_const
		\ , 'is_virtual': l:is_virtual
		\ }))
	let ret =
		\s:CommentBlock(s:Line('@brief ' . l:brief) . l:prototype)
		\. s:Line(s:SpecifyTemplateParams(l:cls_tplparams))
		\. s:Line(s:SpecifyTemplateParams(l:func_tplparams))
		\. s:Line(l:rettype)
		\. s:Qualify(
			\l:namespace,
			\s:Qualify(
				\s:SpecifyTemplateArgs(l:clsname, l:cls_tplparams),
				\l:funcname))
		\. s:Line(
			\'(' . l:funcargs . ')'
			\. s:Fallback(l:is_const, ' const'))
		\. s:Line('{')
		\. s:Line('}')
	return l:ret
endfunction

"retrieves the definition of a constructor
function! s:DefConstructor(...)
	let args = 0 <# a:0 ? a:1 : {}
	let brief = s:Arg(l:args, 'brief')
	let namespace = s:NamespaceArg(args)
	let clsname = s:ClsnameArg(args)
	let completion = {'completion': 'cscope'}
	let funcargs = s:Arg(l:args, 'funcargs', completion)
	let cls_tplparams = s:Arg(l:args, 'cls_tplparams', completion)
	let func_tplparams = s:Arg(l:args, 'func_tplparams', completion)
	return s:DefMemfunc(
		\ { 'namespace': l:namespace
		\ , 'clsname': l:clsname
		\ , 'funcname': l:clsname
		\ , 'funcargs': l:funcargs
		\ , 'rettype': ''
		\ , 'cls_tplparams': l:cls_tplparams
		\ , 'func_tplparams': l:func_tplparams
		\ , 'is_static': 0
		\ , 'is_const': 0
		\ , 'is_virtual': 0
		\ , 'brief': l:brief
		\ , 'with_decl': s:DictValue(l:args, 'with_decl', 'y')
		\ })
endfunction

"retrieves the definition of the default constructor
function! s:DefDefaultConstructor(...)
	let args = 0 <# a:0 ? a:1 : {}
	let namespace = s:NamespaceArg(l:args)
	let clsname = s:ClsnameArg(l:args)
	let completion = {'completion': 'cscope'}
	let tplparams = s:Arg(l:args, 'tplparams', l:completion)
	return s:DefConstructor(
		\ { 'brief': 'default constructor.'
		\ , 'namespace': l:namespace
		\ , 'clsname': l:clsname
		\ , 'funcargs': ''
		\ , 'cls_tplparams': l:tplparams
		\ , 'func_tplparams': ''
		\ , 'with_decl': s:DictValue(l:args, 'with_decl', 'y')
		\ })
endfunction

"retrieves the definition of the copy constructor
function! s:DefCopyConstructor(...)
	let args = 0 <# a:0 ? a:1 : {}
	let namespace = s:NamespaceArg(l:args)
	let clsname = s:ClsnameArg(l:args)
	let completion = {'completion': 'cscope'}
	let tplparams = s:Arg(l:args, 'tplparams', l:completion)
	return s:DefConstructor(
		\ { 'brief': 'copy constructor.'
		\ , 'namespace': l:namespace
		\ , 'clsname': l:clsname
		\ , 'funcargs': l:clsname . ' const & rhs'
		\ , 'cls_tplparams': l:tplparams
		\ , 'func_tplparams': ''
		\ , 'with_decl': s:DictValue(l:args, 'with_decl', 'y')
		\ })
endfunction

"retrieves the definition of the move constructor
function! s:DefMoveConstructor(...)
	let args = 0 <# a:0 ? a:1 : {}
	let namespace = s:NamespaceArg(l:args)
	let clsname = s:ClsnameArg(l:args)
	let completion = {'completion': 'cscope'}
	let tplparams = s:Arg(l:args, 'tplparams', l:completion)
	return s:DefConstructor(
		\ { 'brief': 'move constructor.'
		\ , 'namespace': l:namespace
		\ , 'clsname': l:clsname
		\ , 'funcargs': l:clsname . ' && rhs'
		\ , 'cls_tplparams': l:tplparams
		\ , 'func_tplparams': ''
		\ , 'with_decl': s:DictValue(l:args, 'with_decl', 'y')
		\ })
endfunction

"retrieves the definition of the destructor.
function! s:DefDestructor(...)
	let args = 0 <# a:0 ? a:1 : {}
	let namespace = s:NamespaceArg(l:args)
	let clsname = s:ClsnameArg(l:args)
	let completion = {'completion': 'cscope'}
	let tplparams = s:Arg(l:args, 'tplparams', l:completion)
	return s:DefMemfunc(
		\ { 'brief': 'destructor.'
		\ , 'namespace': l:namespace
		\ , 'clsname': l:clsname
		\ , 'funcname': '~' . l:clsname
		\ , 'funcargs': ''
		\ , 'rettype': ''
		\ , 'cls_tplparams': l:tplparams
		\ , 'func_tplparams': ''
		\ , 'is_static': 0
		\ , 'is_const': 0
		\ , 'is_virtual': 0
		\ , 'with_decl': s:DictValue(l:args, 'with_decl', 'y')
		\ })
endfunction

"retrieves the definition of the clear() member function.
function! s:DefMemfuncClear(...)
	let args = 0 <# a:0 ? a:1 : {}
	let namespace = s:NamespaceArg(args)
	let clsname = s:ClsnameArg(args)
	let completion = {'completion': 'cscope'}
	let tplparams = s:Arg(l:args, 'tplparams', completion)
	return s:DefMemfunc(
		\ { 'brief': 'clears all internal resources.'
		\ , 'namespace': l:namespace
		\ , 'clsname': l:clsname
		\ , 'funcname': 'clear'
		\ , 'funcargs': ''
		\ , 'rettype': 'void'
		\ , 'cls_tplparams': l:tplparams
		\ , 'func_tplparams': ''
		\ , 'is_static': 0
		\ , 'is_const': 0
		\ , 'is_virtual': 0
		\ , 'with_decl': s:DictValue(l:args, 'with_decl', 'y')
		\ })
endfunction

"retrieves the definition of the swap() member function.
function! s:DefMemfuncSwap(...)
	let args = 0 <# a:0 ? a:1 : {}
	let namespace = s:NamespaceArg(args)
	let clsname = s:ClsnameArg(args)
	let completion = {'completion': 'cscope'}
	let tplparams = s:Arg(l:args, 'tplparams', completion)
	return s:DefMemfunc(
		\ { 'brief': 'clears all internal resources.'
		\ , 'namespace': l:namespace
		\ , 'clsname': l:clsname
		\ , 'funcname': 'swap'
		\ , 'funcargs': l:clsname . ' & src'
		\ , 'rettype': 'void'
		\ , 'cls_tplparams': l:tplparams
		\ , 'func_tplparams': ''
		\ , 'is_static': 0
		\ , 'is_const': 0
		\ , 'is_virtual': 0
		\ , 'with_decl': s:DictValue(l:args, 'with_decl', 'y')
		\ })
endfunction

"retrieves the declaration of a function.
function! s:DeclFunc(...)
	let args = 0 <# a:0 ? a:1 : {}
	let completion = {'completion': 'cscope'}
	let funcname = s:Arg(l:args, 'funcname', l:completion)
	let funcargs = s:Arg(l:args, 'funcargs', l:completion)
	let rettype = s:Arg(l:args, 'rettype', l:completion)
	let tplparams = s:Arg(l:args, 'tplparams', l:completion)
	let brief = s:Arg(l:args, 'brief')
	let desc = s:Line('/// ' . l:brief)
		\. s:Line(s:SpecifyTemplateParams(l:tplparams))
		\. s:Line(''
			\. (empty(l:rettype) ? '' : l:rettype . ' ')
			\. l:funcname . '(' . l:funcargs . ');')
		\. s:Newline()
	return l:desc
endfunction

"retrieves the definition of a function.
function! s:DefFunc(...)
	let args = 0 <# a:0 ? a:1 : {}
	let brief = s:Arg(l:args, 'brief')
	let namespace = s:NamespaceArg(l:args)
	let completion = {'completion': 'cscope'}
	let funcname = s:Arg(l:args, 'funcname', l:completion)
	let funcargs = s:Arg(l:args, 'funcargs', l:completion)
	let rettype = s:Arg(l:args, 'rettype', l:completion)
	let tplparams = s:Arg(l:args, 'tplparams', l:completion)
	let with_decl = s:IsYes(s:DictValue(l:args, 'with_decl', 'y'))
	let prototype = s:Fallback(with_decl, s:DeclFunc({
		\'funcname': l:funcname
		\, 'funcargs': l:funcargs
		\, 'rettype': l:rettype
		\, 'tplparams': l:tplparams
		\, 'brief': l:brief
		\}))
	let ret =
		\s:CommentBlock(s:Line('@brief ' . l:brief) . l:prototype)
		\. s:Line(s:SpecifyTemplateParams(l:tplparams))
		\. s:Line(l:rettype)
		\. s:Qualify(l:namespace, l:funcname)
		\. s:Line('(' . l:funcargs . ')')
		\. s:Line('{')
		\. s:Line('}')
	return l:ret
endfunction

"retrieves the definition of a class.
function! s:DefClass(...)
	let args = 0 <# a:0 ? a:1 : {}
	let brief = s:Arg(l:args, 'brief')
	let namespace = s:NamespaceArg(l:args)
	let clsname = s:ClsnameArg(l:args)
	let completion = {'completion': 'cscope'}
	let tplparams = s:Arg(l:args, 'tplparams', l:completion)
	let with_decl = s:IsYes(s:DictValue(l:args, 'with_decl', 'y'))
	let prototype = s:Fallback(with_decl, s:DeclClass(
		\ { 'clsname': l:clsname
		\ , 'tplparams': l:tplparams
		\ , 'brief': l:brief
		\ }))
	let comment = s:CommentBlock(s:Line('@brief ' . l:brief) . l:prototype)
	let public =
		\ s:Line(
			\ 'typedef '
			\ . s:SpecifyTemplateArgs(l:clsname, l:tplparams)
			\ . ' this_type;')
		\ . s:Newline()
		\ . s:DeclDefaultConstructor({ 'clsname': l:clsname })
		\ . s:DeclCopyConstructor({ 'clsname': l:clsname })
		\ . s:DeclMoveConstructor({ 'clsname': l:clsname })
		\ . s:DeclDestructor({ 'clsname': l:clsname })
		\ . s:DeclMemfuncClear()
		\ . s:DeclMemfuncSwap({ 'clsname': l:clsname })
	return l:comment
		\ . s:Line(s:SpecifyTemplateParams(l:tplparams))
		\ . s:Line('class ' . s:Qualify(l:namespace, l:clsname))
		\ . s:Line('{')
		\ . s:Line('public :')
		\ . s:Indent(l:public)
		\ . s:Line('protected :')
		\ . s:Newline()
		\ . s:Line('private :')
		\ . s:Newline()
		\ . s:Line('};')
endfunction

"retrieves the namespace from arguments.
function! s:NamespaceArg(...)
	let args = 0 <# a:0 ? a:1 : {}
	return s:Arg(l:args, 'namespace',
		\ { 'defvalue': s:NamespaceFrom()
		\ , 'completion': 'cscope'
		\ })
endfunction

"retrieves the name of class from arguments.
function! s:ClsnameArg(...)
	let args = 0 <# a:0 ? a:1 : {}
	return s:Arg(l:args, 'clsname',
		\ { 'defvalue': s:ClsnameFrom()
		\ , 'completion': 'cscope'
		\ })
endfunction

"retrieves the declaration of a class.
function! s:DeclClass(...)
	let args = 0 <# a:0 ? a:1 : {}
	let clsname = s:ClsnameArg(l:args)
	let completion = {'completion': 'cscope'}
	let tplparams = s:Arg(l:args, 'tplparams', l:completion)
	let brief = s:Arg(l:args, 'brief')
	let ret = s:Line('/// ' . l:brief)
		\ . s:Line(s:SpecifyTemplateParams(l:tplparams))
		\ . s:Line('class ' . l:clsname)
		\ . s:Newline()
	return l:ret
endfunction

"retrieves the declaration of the destructor.
function! s:DeclDestructor(...)
	let args = 0 <# a:0 ? a:1 : {}
	let clsname = s:ClsnameArg(l:args)
	return s:DeclMemfunc(
		\ { 'brief': 'destructor'
		\ , 'funcname': '~' . l:clsname
		\ , 'funcargs': ''
		\ , 'rettype': ''
		\ , 'tplparams': ''
		\ , 'is_static': ''
		\ , 'is_const': ''
		\ , 'is_virtual': ''
		\ })
endfunction

"retrieves the declaration of a constructor.
function! s:DeclConstructor(...)
	let args = 0 <# a:0 ? a:1 : {}
	let brief = s:Arg(l:args, 'brief')
	let clsname = s:ClsnameArg(args)
	let completion = {'completion': 'cscope'}
	let funcargs = s:Arg(l:args, 'funcargs', completion)
	let tplparams = s:Arg(l:args, 'tplparams', completion)
	return s:DeclMemfunc(
		\ { 'brief': l:brief
		\ , 'funcname': l:clsname
		\ , 'funcargs': l:funcargs
		\ , 'rettype': ''
		\ , 'tplparams': l:tplparams
		\ , 'is_static': ''
		\ , 'is_const': ''
		\ , 'is_virtual': ''
		\ })
endfunction

"retrieves the declaration of the default constructor.
function! s:DeclDefaultConstructor(...)
	let args = 0 <# a:0 ? a:1 : {}
	let clsname = s:ClsnameArg(l:args)
	return s:DeclConstructor(
		\ { 'brief': 'default constructor.'
		\ , 'clsname': l:clsname
		\ , 'funcargs': ''
		\ , 'tplparams': ''
		\ })
endfunction

"retrieves the declaration of the copy constructor.
function! s:DeclCopyConstructor(...)
	let args = 0 <# a:0 ? a:1 : {}
	let clsname = s:ClsnameArg(l:args)
	return s:DeclConstructor(
		\ { 'brief': 'copy constructor.'
		\ , 'clsname': l:clsname
		\ , 'funcargs': l:clsname . ' const & rhs'
		\ , 'tplparams': ''
		\ })
endfunction

"retrieves the declaration of the move constructor.
function! s:DeclMoveConstructor(...)
	let args = 0 <# a:0 ? a:1 : {}
	let clsname = s:ClsnameArg(l:args)
	return s:DeclConstructor(
		\ { 'brief': 'move constructor.'
		\ , 'clsname': l:clsname
		\ , 'funcargs': l:clsname . ' && rhs'
		\ , 'tplparams': ''
		\ })
endfunction

"retrieves the declaration of the clear member function.
function! s:DeclMemfuncClear()
	return s:DeclMemfunc(
		\ { 'brief': 'clears all internal resources.'
		\ , 'funcname': 'clear'
		\ , 'funcargs': ''
		\ , 'rettype': 'void'
		\ , 'tplparams': ''
		\ , 'is_static': ''
		\ , 'is_const': ''
		\ , 'is_virtual': ''
		\ })
endfunction

"retrieves the declaration of the swap member function.
function! s:DeclMemfuncSwap(...)
	let args = 0 <# a:0 ? a:1 : {}
	let clsname = s:ClsnameArg(l:args)
	return s:DeclMemfunc(
		\ { 'brief': 'exchanges resources.'
		\ , 'funcname': 'swap'
		\ , 'funcargs': l:clsname . ' & src'
		\ , 'rettype': 'void'
		\ , 'tplparams': ''
		\ , 'is_static': ''
		\ , 'is_const': ''
		\ , 'is_virtual': ''
		\ })
endfunction

"retrieves the template of a C++ header file.
function! s:CppHeader(...)
	let args = 0 <# a:0 ? a:1 : {}
	let brief = s:Arg(l:args, 'brief')
	let namespace = s:NamespaceArg(args)
	let filename = s:Basename()
	let since = s:Date()
	let include_guard = s:IncludeGuard()
	let ret =
		\ s:CommentBlock(''
			\. s:Line('@file ' . l:filename)
			\. s:Line('@brief ' . l:brief)
			\. s:Line('@since ' . l:since)
			\)
		\ . s:Line('#ifndef ' . l:include_guard)
		\ . s:Line('#define ' . l:include_guard)
		\ . s:CommentHeadline('defines macros.')
		\ . s:CommentHeadline('declares types.')
		\ . s:DefNamespace(l:namespace)
		\ . s:CommentHeadline('declares classes.')
		\ . s:CommentHeadline('declares functions.')
		\ . s:DefNamespace(l:namespace)
		\ . s:CommentHeadline('specializes classes.')
		\ . s:DefNamespace(l:namespace)
		\ . s:CommentHeadline('defines public member functions.')
		\ . s:CommentHeadline('defines protected member functions.')
		\ . s:CommentHeadline('defines private member functions.')
		\ . s:CommentHeadline('defines functions.')
		\ . s:Line('#endif // ' . l:include_guard)
	return l:ret
endfunction

"retrieves the template of a C++ source file.
function! s:CppSource(...)
	let args = 0 <# a:0 ? a:1 : {}
	let brief = s:Arg(l:args, 'brief')
	let namespace = s:NamespaceArg(args)
	let anonymous = s:Qualify(l:namespace, s:Anonymous())
	let filename = s:Basename()
	let since = s:Date()
	let ret =
		\ s:CommentBlock(''
			\. s:Line('@file ' . l:filename)
			\. s:Line('@brief ' . l:brief)
			\. s:Line('@since ' . l:since)
		\)
		\ . s:CommentHeadline('defines macros.')
		\ . s:CommentHeadline('declares types.')
		\ . s:DefNamespace(l:anonymous)
		\ . s:CommentHeadline('defines public member functions.')
		\ . s:CommentHeadline('defines protected member functions.')
		\ . s:CommentHeadline('defines private member functions.')
		\ . s:CommentHeadline('defines global functions.')
		\ . s:CommentHeadline('defines functions.')
		\ . s:DefNamespace(l:anonymous)
	return l:ret
endfunction

"retrieves the template of a C++ class header file.
function! s:CppClassHeader(...)
	let args = 0 <# a:0 ? a:1 : {}
	let brief = s:Arg(l:args, 'brief')
	let namespace = s:NamespaceArg(l:args)
	let clsname = s:ClsnameArg(l:args)
	let completion = {'completion': 'cscope'}
	let tplparams = s:Arg(l:args, 'tplparams', l:completion)
	let filename = s:Basename()
	let since = s:Date()
	let include_guard = s:IncludeGuard()
	let def_cls = s:DefClass(
		\ { 'brief': l:brief
		\ , 'namespace': l:namespace
		\ , 'clsname': l:clsname
		\ , 'tplparams': l:tplparams
		\ , 'with_decl': 'no'
		\ })
	let ret = s:CommentBlock(''
			\ . s:Line('@file ' . l:filename)
			\ . s:Line('@brief ' . l:brief)
			\ . s:Line('@since ' . l:since)
		\ )
		\ . s:Line('#ifndef ' . l:include_guard)
		\ . s:Line('#define ' . l:include_guard)
		\ . s:CommentHeadline('defines macros.')
	if !empty(l:tplparams)
		let ret .=
			\ s:Line('#define ' . g:my.template_params . ' \')
			\ . s:Indent(s:Line(l:tplparams))
			\ . s:Line('#define ' . g:my.template_args . ' \')
			\ . s:Indent(s:Line(s:TemplateArgsFrom(l:tplparams)))
	endif
	let ret .=
		\ s:CommentHeadline('declares types.')
		\ . s:DefNamespace(l:namespace)
		\ . s:CommentHeadline('declares classes.')
		\ . def_cls
		\ . s:CommentHeadline('declares functions.')
		\ . s:DefNamespace(l:namespace)
		\ . s:CommentHeadline('specializes classes.')
		\ . s:DefNamespace(l:namespace)
		\ . s:CommentHeadline('defines public member functions.')
		\ . s:CommentHeadline('defines protected member functions.')
		\ . s:CommentHeadline('defines private member functions.')
		\ . s:CommentHeadline('defines functions.')
	if !empty(l:tplparams)
		let ret .= 
			\ s:CommentHeadline('revokes temporary macros.')
			\ . s:Line('#undef ' . g:my.template_params)
			\ . s:Line('#undef ' . g:my.template_args)
	endif
	let ret .= s:Line('#endif // ' . l:include_guard)
	return l:ret
endfunction

"retrieves the template of a C++ class source file.
function! s:CppClassSource(...)
	let args = 0 <# a:0 ? a:1 : {}
	let brief = s:Arg(l:args, 'brief')
	let namespace = s:NamespaceArg(l:args)
	let clsname = s:ClsnameArg(l:args)
	let completion = {'completion': 'cscope'}
	let tplparams = s:Arg(l:args, 'tplparams', l:completion)
	let anonymous = s:Qualify(l:namespace, s:Anonymous())
	let filename = s:Basename()
	let since = s:Date()
	let options =
		\ { 'namespace': l:namespace
		\ , 'clsname': l:clsname
		\ , 'tplparams': l:tplparams
		\ , 'with_decl': 'no'
		\ }
	let ret =
		\ s:CommentBlock(''
			\ . s:Line('@file ' . l:filename)
			\ . s:Line('@brief ' . l:brief)
			\ . s:Line('@since ' . l:since)
		\ )
		\ . s:CommentHeadline('defines macros.')
		\ . s:CommentHeadline('declares types.')
		\ . s:DefNamespace(l:anonymous)
		\ . s:CommentHeadline('defines public member functions.')
		\ . s:DefDefaultConstructor(options)
		\ . s:DefCopyConstructor(options)
		\ . s:DefMoveConstructor(options)
		\ . s:DefDestructor(options)
		\ . s:DefMemfuncClear(options)
		\ . s:DefMemfuncSwap(options)
		\ . s:CommentHeadline('defines protected member functions.')
		\ . s:CommentHeadline('defines private member functions.')
		\ . s:CommentHeadline('defines global functions.')
		\ . s:CommentHeadline('defines functions.')
		\ . s:DefNamespace(l:anonymous)
	return l:ret
endfunction

"open files.
function! s:Open(...)
	let files = a:000
	if empty(files)
		let pattern = s:Input(
			\{'prompt': 'glob pattern: '
			\, 'completion': 'file'
			\, 'defvalue': expand('%:p')
			\})
		let founds = split(glob(l:pattern), "\n")

		let files = copy(l:files)
		for found in l:founds
			if filereadable(l:found)
				call add(files, l:found)
			endif
		endfor
	endif
	for file in l:files
		execute 'edit ' . l:file
	endfor
endfunction

"search pairs
function! s:SearchPairs(...)
	let args = 0 <# a:0 ? a:1 : {}
	let begin = s:Arg(l:args, 'begin')
	let middle = s:DictValue(l:args, 'middle')
	let end = s:Arg(l:args, 'end')
	let save_cursor = getpos('.')
	"aggregates pairs.
	execute 'normal! gg'
	let pairs = []
	let not_found = [0, 0]
	let found = searchpos(l:begin, 'Wc')
	while 1
		if l:not_found ==# l:found
			break
		endif
		let open_pos = getpos('.')
		let close_pos = searchpairpos(l:begin, l:middle, l:end, 'W')
		if l:not_found ==# l:close_pos
			continue
		endif
		call add(l:pairs, [l:open_pos[1] , l:close_pos[0]])
		call setpos('.', l:open_pos)
		let found = searchpos(l:begin, 'W')
	endwhile
	call setpos('.', l:save_cursor)
	return l:pairs
endfunction

"folds the current scope.
function! s:FoldOuterBrace()
	execute 'normal! [{zf%'
endfunction

"folds all pairs of the current buffer.
function! s:FoldAllPairs(...)
	let args = 0 <# a:0 ? a:1 : {}
	let pairs = s:SearchPairs(args)
	"echo l:pairs
	"creates folds.
	let foldenable = &l:foldenable
	let &l:foldenable = 0
	for pair in l:pairs
		execute string(pair[0]) . ',' . string(pair[1]) . 'fold'
	endfor
	if l:foldenable
		let &l:foldenable = 1
	endif
endfunction

"folds all C/C++ comment blocks in the current buffer.
function! s:FoldAllCommentBlocks()
	call s:FoldAllPairs(
		\ { 'begin': '/\*'
		\ , 'end' : '\*/'
		\ })
endfunction

"folds all functions of the current Vim Script.
function! s:FoldAllVimFunction()
	call s:FoldAllPairs(
		\ { 'begin': '^\<fu\%[nction]\>'
		\ , 'end' : '^\<endf\%[unction]\>'
		\ })
endfunction

"folds all braces of the current buffer.
function! s:FoldAllBraces()
	call s:FoldAllPairs(
		\ { 'begin': '{'
		\ , 'end' : '}'
		\ })
endfunction

"inserts a string with a command.
function! s:InsertAs(pre, str, ...)
	let post = 0 <# a:0 ? a:1 : ''
	let autoindent = &l:autoindent
	let smartindent = &l:smartindent
	let &l:autoindent = 0
	let &l:smartindent = 0
	exec 'normal! ' . a:pre . a:str . "\<ESC>" . post
	if l:autoindent
		let &l:autoindent = 1
	endif
	if l:smartindent
		let &l:smartindent = 1
	endif
endfunction

"appends a string after the current cursor.
function! s:Append(str)
	call s:InsertAs('a', a:str)
endfunction

"inserts a string before the current line.
function! s:InsertLine(str)
	call s:InsertAs('O', a:str)
endfunction

"appends a string below the current line.
function! s:AppendLine(str)
	call s:InsertAs('o', a:str)
endfunction

"retrieves the white spaces as a indent.
function! s:IndentSpace(...)
	let addition = 0 <# a:0 ? a:1 : 0
	let col = virtcol('.')
	let tabstop = &l:tabstop
	return repeat(
		\ ' ',
		\ (l:tabstop * (l:addition + 1)) - (l:col - 1) % l:tabstop)
endfunction
"-------------------------------------------------------------------------------
"functions used from outside of this script
"-------------------------------------------------------------------------------
let g:my={}

"default prefix for namespace.
let g:my.namespace = 'my'

"default macro for template parameters.
let g:my.template_params = 'my_template_params'

"default macro for template arguments.
let g:my.template_args = 'my_template_args'

"retrieves a line
function! my.Line(...)
	let str = 0 <# a:0 ? a:1 : ''
	return s:Line(l:str)
endfunction

"retrieves a linebreak.
function! my.Newline()
	return s:Newline()
endfunction

"retrieves the statusline
function! my.Statusline()
	let enc = s:Encoding()
	let eol = s:EolFormat()
	return (empty(l:enc) ? '' : '[' . l:enc . ']')
		\. (empty(l:eol) ? '' : '[' . l:eol . ']')
endfunction

"retrieves the current date and time as string.
function! my.DateTime(...)
	let time = 0 <# a:0 ? a:1 : localtime()
	return s:DateTime(l:time)
endfunction

"retrieves indent as white space.
function! my.IndentSpace(...)
	let addition = 0 <# a:0 ? a:1 : 0
	return s:IndentSpace(l:addition)
endfunction

"-------------------------------------------------------------------------------
"commands
"-------------------------------------------------------------------------------
command! -nargs=?
	\ DateTime
	\ call s:Append(s:DateTime(<args>))
command! -nargs=? -complete=cscope
	\ DefNamespace
	\ call s:InsertLine(s:DefNamespace(<args>))
command! -nargs=?
	\ CommentHeadline
	\ call s:InsertLine(s:CommentHeadline(<args>))
command! -nargs=?
	\ IncludeGuard
	\ call s:Append(s:IncludeGuard(<args>))
command! -nargs=? -complete=cscope
	\ DeclFunc
	\ call s:InsertLine(s:DeclFunc(<args>))
command! -nargs=? -complete=cscope
	\ DeclClass
	\ call s:InsertLine(s:DeclClass(<args>))
command! -nargs=? -complete=cscope
	\ DeclMemfunc
	\ call s:InsertLine(s:DeclMemfunc(<args>))
command! -nargs=? -complete=cscope
	\ DeclConstructor
	\ call s:InsertLine(s:DeclConstructor(<args>))
command! -nargs=? -complete=cscope
	\ DeclDefaultConstructor
	\ call s:InsertLine(s:DeclDefaultConstructor(<args>))
command! -nargs=? -complete=cscope
	\ DeclCopyConstructor
	\ call s:InsertLine(s:DeclCopyConstructor(<args>))
command! -nargs=? -complete=cscope
	\ DeclMoveConstructor
	\ call s:InsertLine(s:DeclMoveConstructor(<args>))
command! -nargs=? -complete=cscope
	\ DeclDestructor
	\ call s:InsertLine(s:DeclDestructor(<args>))
command! -nargs=? -complete=cscope
	\ DeclMemfuncClear
	\ call s:InsertLine(s:DeclMemfuncClear(<args>))
command! -nargs=? -complete=cscope
	\ DeclMemfuncSwap
	\ call s:InsertLine(s:DeclMemfuncSwap(<args>))
command! -nargs=? -complete=cscope
	\ DefFunc
	\ call s:InsertLine(s:DefFunc(<args>))
command! -nargs=? -complete=cscope
	\ DefMemfunc
	\ call s:InsertLine(s:DefMemfunc(<args>))
command! -nargs=? -complete=cscope
	\ DefConstructor
	\ call s:InsertLine(s:DefConstructor(<args>))
command! -nargs=? -complete=cscope
	\ DefDefaultConstructor
	\ call s:InsertLine(s:DefDefaultConstructor(<args>))
command! -nargs=? -complete=cscope
	\ DefCopyConstructor
	\ call s:InsertLine(s:DefCopyConstructor(<args>))
command! -nargs=? -complete=cscope
	\ DefMoveConstructor
	\ call s:InsertLine(s:DefMoveConstructor(<args>))
command! -nargs=? -complete=cscope
	\ DefDestructor
	\ call s:InsertLine(s:DefDestructor(<args>))
command! -nargs=? -complete=cscope
	\ DefMemfuncClear
	\ call s:InsertLine(s:DefMemfuncClear(<args>))
command! -nargs=? -complete=cscope
	\ DefMemfuncSwap
	\ call s:InsertLine(s:DefMemfuncSwap(<args>))
command! -nargs=? -complete=cscope
	\ DefClass
	\ call s:InsertLine(s:DefClass(<args>))
command! -nargs=?
	\ CommentBlock
	\ call s:InsertLine(s:CommentBlock(<args>))
command! -nargs=? -complete=file
	\ NamespaceFrom
	\ call s:Append(s:NamespaceFrom(<args>))
command! -nargs=? -complete=file
	\ ClsnameFrom
	\ call s:Append(s:ClsnameFrom(<args>))
command! -nargs=? -complete=cscope
	\ DefaultNamespace
	\ call s:DefaultNamespace(<args>)
command! -nargs=? -complete=cscope
	\ DefaultTemplateParams
	\ call s:DefaultTemplateParams(<args>)
command! -nargs=? -complete=cscope
	\ DefaultTemplateArgs
	\ call s:DefaultTemplateArgs(<args>)
command! -nargs=? -complete=cscope
	\ TemplateParamsFrom
	\ call s:Append(s:TemplateParamsFrom(<args>))
command! -nargs=? -complete=cscope
	\ TemplateArgsFrom
	\ call s:Append(s:TemplateArgsFrom(<args>))
command! -nargs=* -complete=file Open
	\ call s:Open(<f-args>)
command! -nargs=?
	\ CppHeader
	\ call s:AppendLine(s:CppHeader(<args>))
command! -nargs=?
	\ CppSource
	\ call s:AppendLine(s:CppSource(<args>))
command! -nargs=?
	\ CppClassHeader
	\ call s:AppendLine(s:CppClassHeader(<args>))
command! -nargs=?
	\ CppClassSource
	\ call s:AppendLine(s:CppClassSource(<args>))
command! -nargs=0
	\ FoldOuterBrace
	\ call s:FoldOuterBrace()
command! -nargs=0
	\ FoldAllBraces
	\ call s:FoldAllBraces()
command! -nargs=0
	\ FoldAllVimFunction
	\ call s:FoldAllVimFunction()
command! -nargs=0
	\ FoldAllCommentBlocks
	\ call s:FoldAllCommentBlocks()
command! -nargs=?
	\ SearchPairs
	\ echo s:SearchPairs(<args>)
command! -nargs=?
	\ IndentSpace
	\ echo s:InsertAs('i', s:IndentSpace(<args>), 'l')

