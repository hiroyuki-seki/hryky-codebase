#----------------------------------------------------------------
=begin
= mkdir.rb

== brief
�f�B���N�g���̍쐬

== since
2007-12-22 20:53:03

== author
HRYKY

== version
$Id: mkdir.rb 709 2008-12-13 17:44:56Z hryky $

=end
#----------------------------------------------------------------

require "optparse"
require "fileutils"

#----------------------------------------------------------------
=begin
== �N���X(class definition)
=end
#----------------------------------------------------------------

#----------------------------------------------------------------
=begin
== ���\�b�h(method definition)
=end
#----------------------------------------------------------------

#----------------------------------------------------------------
=begin
== ������(execution)
=end
#----------------------------------------------------------------
if File.expand_path($0) == File.expand_path(__FILE__)

  verbose = false
  recursive = false

  opt_parser = OptionParser.new

  # �ڍ׏o��
  opt_parser.on("-v", "--verbose") { |boolean| verbose = boolean }

  # �e�f�B���N�g���쐬
  opt_parser.on("-p", "--parents") { |boolean| recursive = boolean }

  # ������]��
  directories = opt_parser.order(ARGV)

  directories.each { |directory|

    next if FileTest.exist?(directory)

    if recursive
      FileUtils.mkdir_p(directory, {:verbose => verbose})
    else
      FileUtils.mkdir(directory, {:verbose => verbose})
    end
  }

end
