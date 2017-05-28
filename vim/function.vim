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

"retrieves the indented lines.
function! s:Indent(...)
	let lines = 0 <# a:0 ? a:1 : ''
	let prefix = 1 <# a:0 ? a:2 : "\t"
	let desc = substitute(l:lines, '^', l:prefix, '')
	let desc = substitute(l:desc, "\\n", "\n" . l:prefix, 'g')
	return l:desc
endfunction

"retrieves a block comment
function! s:CommentBlock(...)
	let desc = 0 <# a:0 ? a:1 : s:Input()
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
		\{'prompt': 'default namespace is : '
		\, 'defvalue': g:hryky.namespace
		\, 'completion': 'cscope'
		\})
endfunction

"assigns the default template parameters.
function! s:DefaultTemplateParams(...)
	let g:hryky.template_params = 0 <# a:0 ? a:1 : s:Input(
		\{'prompt': 'macro for template parameters is : '
		\, 'defvalue': g:hryky.template_params
		\, 'completion': 'cscope'
		\})
endfunction

"assigns the default template arguments.
function! s:DefaultTemplateArgs(...)
	let g:hryky.template_args = 0 <# a:0 ? a:1 : s:Input(
		\{'prompt': 'macro for template arguments is : '
		\, 'defvalue': g:hryky.template_args
		\, 'completion': 'cscope'
		\})
endfunction

"constructs template parameters from a string.
function! s:TemplateParamsFrom(...)
	let str = 0 <# a:0 ? a:1 : ''
	if empty(l:str)
		return ''
	endif
	let ret = l:str is# s:Anonymous() ? g:hryky.template_params : l:str
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
		return g:hryky.template_args
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

"retrieves the filename of the current buffer.
function! s:Filename()
	return expand('%:t:r')
endfunction

"constructs namespace components from a string.
function! s:ComponentsFrom(...)
	let str = s:Qualify(
		\g:hryky.namespace
		\, 0 <# a:0 ? a:1 : s:Filename())
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
	let funcname = s:Arg(l:args, 'funcname', completion)
	let funcargs = s:Arg(l:args, 'funcargs', completion)
	let rettype = s:Arg(l:args, 'rettype', completion)
	let is_static = s:IsYes(s:Arg(l:args, 'is_static'))
	let is_const = !is_static && s:IsYes(s:Arg(l:args, 'is_const'))
	let is_virtual = !is_static && s:IsYes(s:Arg(l:args, 'is_virtual'))
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
	let namespace = s:Arg(l:args, 'namespace',
		\{'defvalue': s:NamespaceFrom()
		\, 'completion': 'cscope'
		\})
	let clsname = s:Arg(l:args, 'clsname',
		\{'defvalue': s:ClsnameFrom()
		\, 'completion': 'cscope'
		\})
	let completion = {'completion': 'cscope'}
	let funcname = s:Arg(l:args, 'funcname', completion)
	let funcargs = s:Arg(l:args, 'funcargs', completion)
	let rettype = s:Arg(l:args, 'rettype', completion)
	let tplparams = s:Arg(l:args, 'tplparams', completion)
	let is_static = s:IsYes(s:Arg(l:args, 'is_static'))
	let is_const = !is_static && s:IsYes(s:Arg(l:args, 'is_const'))
	let is_virtual = !is_static && s:IsYes(s:Arg(l:args, 'is_virtual'))
	let brief = s:Arg(l:args, 'brief')
	let ret =
		\s:CommentBlock(
		\s:Line('@brief ' . l:brief)
		\. s:DeclMemfunc({
			\'funcname': l:funcname
			\, 'funcargs': l:funcargs
			\, 'rettype': l:rettype
			\, 'is_static': l:is_static
			\, 'is_const': l:is_const
			\, 'is_virtual': l:is_virtual
			\, 'brief': l:brief
			\})
		\)
		\. s:Line(s:SpecifyTemplateParams(l:tplparams))
		\. s:Line(l:rettype)
		\. s:Qualify(
			\l:namespace,
			\s:Qualify(
				\s:SpecifyTemplateArgs(l:clsname, l:tplparams),
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
	let completion = {'completion': 'cscope'}
	let funcname = s:Arg(l:args, 'funcname', completion)
	let funcargs = s:Arg(l:args, 'funcargs', completion)
	let rettype = s:Arg(l:args, 'rettype', completion)
	let tplparams = s:Arg(l:args, 'tplparams', completion)
	let brief = s:Arg(l:args, 'brief')
	let desc = s:Line('/// ' . l:brief)
		\. s:Line(s:SpecifyTemplateParams(l:tplparams))
		\. s:Line(l:rettype . ' ' . l:funcname . '(' . l:funcargs . ');')
	return l:desc
endfunction

"retrieves the definition of a function.
function! s:DefFunc(...)
	let args = 0 <# a:0 ? a:1 : {}
	let namespace = s:Arg(l:args, 'namespace',
		\{'defvalue': s:NamespaceFrom()
		\, 'completion': 'cscope'
		\})
	let completion = {'completion': 'cscope'}
	let funcname = s:Arg(l:args, 'funcname', completion)
	let funcargs = s:Arg(l:args, 'funcargs', completion)
	let rettype = s:Arg(l:args, 'rettype', completion)
	let tplparams = s:Arg(l:args, 'tplparams', completion)
	let brief = s:Arg(l:args, 'brief')
	let ret =
		\s:CommentBlock(
		\s:Line('@brief ' . l:brief)
		\. s:DeclFunc({
			\'funcname': l:funcname
			\, 'funcargs': l:funcargs
			\, 'rettype': l:rettype
			\, 'tplparams': l:tplparams
			\, 'brief': l:brief
			\})
		\)
		\. s:Line(s:SpecifyTemplateParams(l:tplparams))
		\. s:Line(l:rettype)
		\. s:Qualify(l:namespace, l:funcname)
		\. s:Line('(' . l:funcargs . ')')
		\. s:Line('{')
		\. s:Line('}')
	return l:ret
endfunction

"retrieves the template of a C++ header file.
function! s:CppHeader(...)
	let args = 0 <# a:0 ? a:1 : {}
	let brief = s:Arg(l:args, 'brief')
	let namespace = s:Arg(l:args, 'namespace',
		\{'defvalue': s:NamespaceFrom()
		\, 'completion': 'cscope'
		\})
	let filename = s:Filename()
	let since = s:Date()
	let ret = s:CommentBlock(''
		\. s:Line('@file ' . l:filename)
		\. s:Line('@brief ' . l:brief)
		\. s:Line('@since ' . l:since)
		\)
	let include_guard = s:IncludeGuard()
	let ret .= s:Line('#ifndef ' . l:include_guard)
	let ret .= s:Line('#define ' . l:include_guard)
	let ret .= s:CommentHeadline('defines macros.')
	let ret .= s:CommentHeadline('declares types.')
	let ret .= s:DefNamespace(l:namespace)
	let ret .= s:CommentHeadline('declares classes.')
	let ret .= s:CommentHeadline('declares functions.')
	let ret .= s:DefNamespace(l:namespace)
	let ret .= s:CommentHeadline('specializes classes.')
	let ret .= s:DefNamespace(l:namespace)
	let ret .= s:CommentHeadline('defines public member functions.')
	let ret .= s:CommentHeadline('defines protected member functions.')
	let ret .= s:CommentHeadline('defines private member functions.')
	let ret .= s:CommentHeadline('defines functions.')
	let ret .= s:Line('#endif // ' . l:include_guard)
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

"folds the current scope.
function! s:FoldOuterBrace()
	execute 'normal! [{zf%'
endfunction

"inserts a string with a command.
function! s:InsertAs(command, str)
	let autoindent = &l:autoindent
	let smartindent = &l:smartindent
	let &l:autoindent = 0
	let &l:smartindent = 0
	exec 'normal! ' . a:command . a:str
	if l:autoindent
		let &l:autoindent = 1
	endif
	if l:smartindent
		let &l:smartindent = 1
	endif
endfunction

"inserts a string under the current cursor.
function! s:Insert(str)
	call s:InsertAs('i', a:str)
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
	return s:DateTime(l:time)
endfunction

"-------------------------------------------------------------------------------
"commands
"-------------------------------------------------------------------------------
command! -nargs=? -complete=cscope
	\ DefNamespace
	\ call s:AppendLine(s:DefNamespace(<args>))
command! -nargs=?
	\ CommentHeadline
	\ call s:AppendLine(s:CommentHeadline(<args>))
command! -nargs=?
	\ IncludeGuard
	\ call s:Append(s:IncludeGuard(<args>))
command! -nargs=? -complete=cscope
	\ DeclFunc
	\ call s:AppendLine(s:DeclFunc(<args>))
command! -nargs=? -complete=cscope
	\ DeclMemfunc
	\ call s:AppendLine(s:DeclMemfunc(<args>))
command! -nargs=? -complete=cscope
	\ DefFunc
	\ call s:AppendLine(s:DefFunc(<args>))
command! -nargs=? -complete=cscope
	\ DefMemfunc
	\ call s:AppendLine(s:DefMemfunc(<args>))
command! -nargs=?
	\ CommentBlock
	\ call s:AppendLine(s:CommentBlock(<args>))
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
command! -nargs=0
	\ FoldOuterBrace
	\ call s:FoldOuterBrace()

