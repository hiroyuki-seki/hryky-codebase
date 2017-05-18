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

"retrieves a comment line as a border.
function! s:CommentBorder()
	return '//' . repeat('-', 78)
endfunction

"call input() conservatively.
function! s:Input(prompt, ...)
	let text = 0 <# a:0 ? a:1 : ''
	let completion = 1 <# a:0 ? a:2 : ''
	call inputsave()
	if empty(l:completion)
		let input = input(a:prompt, l:text)
	else
		let input = input(a:prompt, l:text, l:completion)
	endif
	call inputrestore()
	return l:input
endfunction

"retrieves the definition of C++ namespace.
function! s:DefNamespace(...)
	let args = 0 <# a:0 ? a:1 : {}
	let str = (has_key(l:args,'namespace')
		\? l:args['namespace']
		\: s:Input('namespace is: ', '', 'cscope'))
	let namespaces = split(l:str, ':\+')
	let ret = ''
	for namespace in l:namespaces
		if '*' is# l:namespace
			let namespace = ''
		else
			let namespace = ' ' . l:namespace
		endif
		let ret .= 'namespace' . l:namespace . " {\<CR>"
	endfor
	for namespace in reverse(l:namespaces)
		if '*' is# l:namespace
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
	let str = 0 <# a:0 ? a:1 : s:Input('description is: ')
	return s:Line(s:CommentBorder())
		\. s:Line('// ' . l:str)
		\. s:Line(s:CommentBorder())
endfunction

"retrieves an Include Guard used as a macro.
function! s:IncludeGuard(...)
	let name = 0 <# a:0 ? a:1 : expand('%:t') . g:hryky.DateTime()
	return toupper(
		\substitute(
			\substitute(l:name , '\W', '_', 'g'),
			\'_\+', '_', 'g'))
endfunction

"retrieves the argument from the dictionary.
function! s:Arg(dict, key, ...)
	let defvalue = 0 <# a:0 ? a:1 : ''
	let has_key = has_key(a:dict, a:key)
	if 1 <# a:0
		let ret = l:has_key
			\? a:dict[a:key]
			\: s:Input(a:key.' is: ', l:defvalue, a:2)
	else
		let ret = l:has_key
			\? a:dict[a:key]
			\: s:Input(a:key.' is: ', l:defvalue)
	endif
	return ret
endfunction

"retrieves a line.
function! s:Line(...)
	let str = 0 <# a:0 ? a:1 : ''
	return l:str . "\n"
endfunction

"retrieves the indented lines.
function! s:Indent(...)
	let lines = 0 <# a:0 ? a:1 : ''
	let prefix = 1 <# a:0 ? a:2 : "\t"
	let desc = substitute(l:lines, '^', l:prefix, 'g')
	return l:desc
endfunction

"retrieves a block comment
function! s:CommentBlock(...)
	let desc = 0 <# a:0 ? a:1 : s:Input('desc is: ', '')
	let ret =
		\s:Line('/**')
		\. s:Indent(desc, '  ')
		\. (0 <# strlen(l:desc) ? s:Line() : '')
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
	let g:hryky.namespace = 0 <# a:0 ? a:1 : s:Input(
		\'default namespace is : ',
		\g:hryky.namespace,
		\'cscope')
endfunction

"assigns the default template parameters.
function! s:DefaultTemplateParams(...)
	let g:hryky.template_params = 0 <# a:0 ? a:1 : s:Input(
		\'macro for template parameters is : ',
		\g:hryky.template_params,
		\'cscope')
endfunction

"assigns the default template arguments.
function! s:DefaultTemplateArgs(...)
	let g:hryky.template_args = 0 <# a:0 ? a:1 : s:Input(
		\'macro for template arguments is : ',
		\g:hryky.template_args,
		\'cscope')
endfunction

"constructs template parameters from a string.
function! s:TemplateParamsFrom(...)
	let str = 0 <# a:0 ? a:1 : ''
	if empty(l:str)
		return ''
	endif
	let ret = l:str is# '*' ? g:hryky.template_params : l:str
	return l:ret
endfunction

"constructs template arguments from a string.
function! s:TemplateArgsFrom(...)
	let str = 0 <# a:0 ? a:1 : ''
	if empty(l:str)
		return ''
	endif
	if l:str is# '*'
		return g:hryky.template_args
	endif
	let params = split(str, '\s*,\s*')
	let args = []
	for param in l:params
		call add(l:args, split(param, '\s\+')[-1])
	endfor
	return join(args, ', ')
endfunction

"constructs namespace components from a string.
function! s:ComponentsFrom(...)
	let str = s:Qualify(
		\g:hryky.namespace
		\, 0 <# a:0 ? a:1 : expand('%:t:r'))
	let components = tolower(
		\substitute(
			\substitute(l:str, '\(\u\+\)', ' \1', 'g')
			\, '\W\+', ' ', 'g'))
	let ret = split(components, '\s\+')
	if !empty(l:ret)
		let ret[-1] = toupper(strpart(l:ret[-1], 0, 1))
			\. strpart(l:ret[-1], 1)
	endif
	return l:ret
endfunc

"constructs a namespace from a string.
function! s:NamespaceFrom(...)
	let str = 0 <# a:0 ? a:1 : expand('%:t:r')
	let components = s:ComponentsFrom(l:str)
	if !empty(l:components)
		let components = l:components[:-2]
	endif
	let ret = s:JoinNamespace(l:components)
	return l:ret
endfunction

"constructs a name of class from a string
function! s:ClsnameFrom(...)
	let str = 0 <# a:0 ? a:1 : expand('%:t:r')
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
	let funcname = s:Arg(l:args, 'funcname', '', 'cscope')
	let funcargs = s:Arg(l:args, 'funcargs')
	let rettype = s:Arg(l:args, 'rettype', '', 'cscope')
	let is_static = s:IsYes(s:Arg(l:args, 'is_static', '', 'cscope'))
	let is_const = !is_static
		\ && s:IsYes(s:Arg(l:args, 'is_const', '', 'cscope'))
	let is_virtual = !is_static
		\ && s:IsYes(s:Arg(l:args, 'is_virtual', '', 'cscope'))
	let brief = s:Arg(l:args, 'brief')
	let ret = s:Line('/// ' . l:brief)
		\. s:Line(
			\s:Fallback(l:is_static, 'static ')
			\. s:Fallback(l:is_virtual, 'virtual ')
			\. l:rettype . ' ' . l:funcname . '(' . l:funcargs . ')'
			\. s:Fallback(l:is_const, ' const')
			\. ';')
	return l:ret
endfunction

"retrieves the definition of a member function.
function! s:DefMemfunc(...)
	let args = 0 <# a:0 ? a:1 : {}
	let namespace = s:Arg(l:args, 'namespace', s:NamespaceFrom(), 'cscope')
	let clsname = s:Arg(l:args, 'clsname', s:ClsnameFrom(), 'cscope')
	let funcname = s:Arg(l:args, 'funcname', '', 'cscope')
	let funcargs = s:Arg(l:args, 'funcargs')
	let rettype = s:Arg(l:args, 'rettype', '', 'cscope')
	let tplparams = s:Arg(l:args, 'template params', '', 'cscope')
	let is_static = s:IsYes(s:Arg(l:args, 'is_static', '', 'cscope'))
	let is_const = !is_static
		\ && s:IsYes(s:Arg(l:args, 'is_const', '', 'cscope'))
	let is_virtual = !is_static
		\ && s:IsYes(s:Arg(l:args, 'is_virtual', '', 'cscope'))
	let brief = s:Arg(l:args, 'brief')
	let ret =
		\s:CommentBlock(
		\s:Line('@brief ' . l:brief)
		\. s:DeclFunc({
			\'funcname': l:funcname
			\, 'funcargs': l:funcargs
			\, 'rettype': l:rettype
			\, 'is_static': l:is_static
			\, 'is_const': l:is_const
			\, 'is_virtual': l:is_virtual
			\, 'brief': l:brief
			\})
		\)
		\. s:Fallback(
			\!empty(l:tplparams),
			\s:Line('template <' . s:TemplateParamsFrom(l:tplparams) . ' >'))
		\. s:Line(l:rettype)
		\. s:Qualify(
			\l:namespace,
			\s:Qualify(
				\l:clsname . s:Fallback(
					\!empty(l:tplparams),
					\'<' . s:TemplateArgsFrom(l:tplparams) . ' >'),
				\l:funcname))
		\. s:Line(
			\'(' . l:funcargs . ')'
			\. s:Fallback(l:is_const, ' const'))
		\. s:Line('{')
		\. s:Line('}')
	return l:ret
endfunction

"retrieves the declaration of a function.
function! s:DeclFunc(...)
	let args = 0 <# a:0 ? a:1 : {}
	let funcname = s:Arg(l:args, 'funcname', '', 'cscope')
	let funcargs = s:Arg(l:args, 'funcargs')
	let rettype = s:Arg(l:args, 'rettype', '', 'cscope')
	let brief = s:Arg(l:args, 'brief')
	let desc = s:Line('/// ' . l:brief)
		\. s:Line(l:rettype . ' ' . l:funcname . '(' . l:funcargs . ');')
	return l:desc
endfunction

"retrieves the definition of a function.
function! s:DefFunc(...)
	let args = 0 <# a:0 ? a:1 : {}
	let namespace = s:Arg(l:args, 'namespace', '', 'cscope')
	let funcname = s:Arg(l:args, 'funcname', '', 'cscope')
	let funcargs = s:Arg(l:args, 'funcargs')
	let rettype = s:Arg(l:args, 'rettype', '', 'cscope')
	let brief = s:Arg(l:args, 'brief')
	let ret =
		\s:CommentBlock(
		\s:Line('@brief ' . l:brief)
		\. s:DeclFunc({
			\'funcname': l:funcname
			\, 'funcargs': l:funcargs
			\, 'rettype': l:rettype
			\, 'brief': l:brief
			\})
		\)
		\. s:Line(l:rettype)
		\. s:Qualify(l:namespace, l:funcname)
		\. s:Line('(' . l:funcargs . ')')
		\. s:Line('{')
		\. s:Line('}')
	return l:ret
endfunction

"inserts a string.
function! s:Insert(str)
	let autoindent = &l:autoindent
	let smartindent = &l:smartindent
	let &l:autoindent = 0
	let &l:smartindent = 0
	exec 'normal! i' . a:str
	if l:autoindent
		let &l:autoindent = 1
	endif
	if l:smartindent
		let &l:smartindent = 1
	endif
endfunction

"-------------------------------------------------------------------------------
"functions used from outside of this script
"-------------------------------------------------------------------------------
let g:hryky={}

"default prefix for namespace.
let g:hryky.namespace = 'hryky'

"default macro for template parameters.
let g:hryky.template_params = 'hryky_template_params'

"default macro for template arguments.
let g:hryky.template_args = 'hryky_template_args'

"retrieves the statusline
function! hryky.Statusline()
	let enc = s:Encoding()
	let eol = s:EolFormat()
	return (empty(l:enc) ? '' : '[' . l:enc . ']')
		\. (empty(l:eol) ? '' : '[' . l:eol . ']')
endfunction

"retrieves the current date and time as string.
function! hryky.DateTime(...)
	let time = 0 <# a:0 ? a:1 : localtime()
	return s:Date(l:time) . 'T' . s:Time(l:time)
endfunction

"-------------------------------------------------------------------------------
"commands
"-------------------------------------------------------------------------------
command! -nargs=0 DefNamespace call s:Insert(s:DefNamespace())
command! -nargs=? CommentHeadline call s:Insert(s:CommentHeadline(<args>))
command! -nargs=? IncludeGuard call s:Insert(s:IncludeGuard(<args>))
command! -nargs=? DeclFunc call s:Insert(s:DeclFunc(<args>))
command! -nargs=? DeclMemfunc call s:Insert(s:DeclMemfunc(<args>))
command! -nargs=? DefFunc call s:Insert(s:DefFunc(<args>))
command! -nargs=? DefMemfunc call s:Insert(s:DefMemfunc(<args>))
command! -nargs=? CommentBlock call s:Insert(s:CommentBlock(<args>))
command! -nargs=? NamespaceFrom call s:Insert(s:NamespaceFrom(<args>))
command! -nargs=? ClsnameFrom call s:Insert(s:ClsnameFrom(<args>))
command! -nargs=? DefaultNamespace call s:DefaultNamespace(<args>)
command! -nargs=? DefaultTemplateParams call s:DefaultTemplateParams(<args>)
command! -nargs=? DefaultTemplateArgs call s:DefaultTemplateArgs(<args>)
command! -nargs=? TemplateParamsFrom call s:Insert(s:TemplateParamsFrom(<args>))
command! -nargs=? TemplateArgsFrom call s:Insert(s:TemplateArgsFrom(<args>))

