#----------------------------------------------------------------
=begin
= remove.rb

== brief
ファイル・ディレクトリの削除

== since
2008-05-03 22:37:45

== author
HRYKY

== version
$Id: remove.rb 735 2009-10-13 15:12:42Z hryky $

=end
#----------------------------------------------------------------

require "optparse"
require "fileutils"

#----------------------------------------------------------------
=begin
== クラス(class definition)
=end
#----------------------------------------------------------------

#----------------------------------------------------------------
=begin
== メソッド(method definition)
=end
#----------------------------------------------------------------

#----------------------------------------------------------------
=begin
== 実処理(execution)
=end
#----------------------------------------------------------------
if File.expand_path($0) == File.expand_path(__FILE__)

  options = Hash.new
  option_parser = OptionParser.new

  # 詳細出力
  option_parser.on("-v", "--verbose") { |boolean| options["verbose"] = boolean }

  # 強制削除
  option_parser.on("-f", "--force") { |boolean| options["force"] = boolean }

  # オプション解析
  option_parser.order!(ARGV)

  if 1 > ARGV.size
    $stderr << "WARNING : neither file nor directory is specified.\n"
    exit 0
  end

  # 削除対象
  sources = ARGV[0..-1]

  #--------------------------------
  # attention
  # rm_r has vulnerability of time-of-check to time-to-use
  #--------------------------------

  FileUtils.rm_r(
    sources, {:verbose => options["verbose"], :force => options["force"]}
  )

end
