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
	let enc = empty(enc) ? &encoding : enc
	return enc.(&l:bomb?'+BOM':'')
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
	return '//'.repeat('-',78)
endfunction

"call input() conservatively.
function! s:Input(prompt, ...)
	let text = 0 <# a:0 ? a:1 : ''
	let completion = 1 <# a:0 ? a:2 : ''
	call inputsave()
	if empty(completion)
		let input = input(a:prompt, text)
	else
		let input = input(a:prompt, text, completion)
	endif
	call inputrestore()
	return input
endfunction

"retrieves the definition of C++ namespace.
function! s:DefNamespace(...)
	let args = 0 <# a:0 ? a:1 : {}
	let str = (has_key(args,'namespace')
		\? args['namespace']
		\: s:Input('namespace is: ', '', 'cscope'))
	let namespaces = split(str, ':\+')
	let ret = ''
	for namespace in namespaces
		if '*' ==# namespace
			let namespace = ''
		endif
		let ret .= 'namespace '.namespace." {\<CR>"
	endfor
	for namespace in reverse(namespaces)
		if '*' ==# namespace
			let namespace = ''
		endif
		let ret .= '}// namespace '.namespace."\<CR>"
	endfor
	echom 'DefNamespace()=>'.ret
	return ret
endfunction

"retrieves comment lines as a headline.
function! s:CommentHeadline(...)
	let str = 0 <# a:0 ? a:1 : s:Input('description is: ')
	return s:CommentBorder()."\n"
		\.'// '.str."\n"
		\.s:CommentBorder()."\n"
endfunction

"retrieves an Include Guard used as a macro.
function! s:IncludeGuard()
	return toupper(
		\substitute(
			\substitute(expand('%:t').g:hryky.DateTime(),"[\-\:]",'','g'),
			\"[\.\-]",'_','g'))
endfunction

"retrieves the argument from the dictionary.
function! s:Arg(dict, key, ...)
	let defvalue = 0 <# a:0 ? a:1 : ''
	let has_key = has_key(a:dict, a:key)
	if 1 <# a:0
		let ret = has_key ? a:dict[a:key] : s:Input(a:key.' is: ', defvalue, a:2)
	else
		let ret = has_key ? a:dict[a:key] : s:Input(a:key.' is: ', defvalue)
	endif
	return ret
endfunction

"retrieves the declaration of a function.
function! s:DeclFunction(...)
	let args = 0 <# a:0 ? a:1 : {}
	let funcname = s:Arg(args, 'funcname', '', 'cscope')
	let funcargs = s:Arg(args, 'funcargs')
	let rettype = s:Arg(args, 'rettype', '', 'cscope')
	let brief = s:Arg(args, 'brief')
	let desc = '/// '.brief."\n".rettype.' '.funcname.'('.funcargs.');'
	return desc
endfunction

"retrieves the definition of a function.
function! s:DefFunction(...)
	let args = 0 <# a:0 ? a:1 : {}
	let namespace = s:Arg(args, 'namespace', '', 'cscope')
	let funcname = s:Arg(args, 'funcname', '', 'cscope')
	let funcargs = s:Arg(args, 'funcargs')
	let rettype = s:Arg(args, 'rettype', '', 'cscope')
	let brief = s:Arg(args, 'brief')
	let desc = 
		\"/**\n"
		\.'  @brief '.brief."\n"
		\.s:DeclFunction({
			\'funcname':funcname
			\, 'funcargs':funcargs
			\, 'rettype':rettype
			\, 'brief':brief
			\})."\n"
		\." */\n"
		\.rettype."\n"
		\.namespace.'::'.funcname.'('.funcargs.")\n"
		\."{\n"
		\."}\n"
	return desc
endfunction

"-------------------------------------------------------------------------------
"functions used from outside of this script
"-------------------------------------------------------------------------------
let g:hryky={}

"retrieves the statusline
function! hryky.Statusline()
	let enc = s:Encoding()
	let eol = s:EolFormat()
	return (empty(enc)?'':'['.enc.']')
		\.(empty(eol)?'':'['.eol.']')
endfunction

"retrieves the current date and time as string.
function! hryky.DateTime(...)
	let time = 0 <# a:0 ? a:1 : localtime()
	return s:Date(time) . 'T' . s:Time(time)
endfunction

"inserts a string.
function! s:InsertExec(str)
	let autoindent = &l:autoindent
	let smartindent = &l:smartindent
	let &l:autoindent = 0
	let &l:smartindent = 0
	exec 'normal i'.a:str
	if autoindent
		let &l:autoindent = 1
	endif
	if smartindent
		let &l:smartindent = 1
	endif
endfunction

"-------------------------------------------------------------------------------
"commands
"-------------------------------------------------------------------------------
command! -nargs=0 DefNamespace call s:InsertExec(s:DefNamespace())
command! -nargs=? CommentHeadline call s:InsertExec(s:CommentHeadline(<args>))
command! -nargs=0 IncludeGuard call s:InsertExec(s:IncludeGuard())
command! -nargs=0 DeclFunction call s:InsertExec(s:DeclFunction())
command! -nargs=0 DefFunction call s:InsertExec(s:DefFunction())

