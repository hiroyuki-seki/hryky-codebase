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
	echom 'DefNamespace()=>' . l:ret
	return l:ret
endfunction

"retrieves comment lines as a headline.
function! s:CommentHeadline(...)
	let str = 0 <# a:0 ? a:1 : s:Input('description is: ')
	return s:CommentBorder() . "\n"
		\. '// ' . l:str . "\n"
		\. s:CommentBorder() . "\n"
endfunction

"retrieves an Include Guard used as a macro.
function! s:IncludeGuard()
	return toupper(
		\substitute(
			\substitute(
				expand('%:t') . g:hryky.DateTime(), "[\-\:]", '', 'g'),
			\"[\.\-]", '_', 'g'))
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

"retrieves the declaration of a function.
function! s:DeclFunction(...)
	let args = 0 <# a:0 ? a:1 : {}
	let funcname = s:Arg(l:args, 'funcname', '', 'cscope')
	let funcargs = s:Arg(l:args, 'funcargs')
	let rettype = s:Arg(l:args, 'rettype', '', 'cscope')
	let brief = s:Arg(l:args, 'brief')
	let desc = '/// ' . l:brief . "\n" . l:rettype . ' ' . l:funcname . '(' . l:funcargs . ');'
	return l:desc
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
	let desc = substitute(l:lines, "^", l:prefix, 'g')
	return l:desc
endfunction

"retrieves a block comment
function! s:CommentBlock(...)
	let args = 0 <# a:0 ? a:1 : {}
	let brief = s:Arg(l:args, 'brief', '')
	let details = s:Arg(l:args, 'details', '')
	let desc =
		\s:Line('/**')
		\. s:Indent(
			\s:Line('@brief ' . l:brief)
			\, '  '
			\)
		\. s:Line(' */')
	return l:desc
endfunction

"retrieves the definition of a function.
function! s:DefFunction(...)
	let args = 0 <# a:0 ? a:1 : {}
	let namespace = s:Arg(l:args, 'namespace', '', 'cscope')
	let funcname = s:Arg(l:args, 'funcname', '', 'cscope')
	let funcargs = s:Arg(l:args, 'funcargs')
	let rettype = s:Arg(l:args, 'rettype', '', 'cscope')
	let brief = s:Arg(l:args, 'brief')
	let desc =
		\"/**\n"
		\. '  @brief ' . l:brief . "\n"
		\. s:DeclFunction({
			\'funcname': l:funcname
			\, 'funcargs': l:funcargs
			\, 'rettype': l:rettype
			\, 'brief': l:brief
			\}) . "\n"
		\. " */\n"
		\. l:rettype . "\n"
		\. l:namespace . '::' . l:funcname . '(' . l:funcargs . ")\n"
		\. "{\n"
		\. "}\n"
	return l:desc
endfunction

"inserts a string.
function! s:InsertExec(str)
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
command! -nargs=0 DefNamespace call s:InsertExec(s:DefNamespace())
command! -nargs=? CommentHeadline call s:InsertExec(s:CommentHeadline(<args>))
command! -nargs=0 IncludeGuard call s:InsertExec(s:IncludeGuard())
command! -nargs=0 DeclFunction call s:InsertExec(s:DeclFunction())
command! -nargs=0 DefFunction call s:InsertExec(s:DefFunction())
command! -nargs=0 CommentBlock call s:InsertExec(s:CommentBlock())

