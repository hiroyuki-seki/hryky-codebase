#! ruby -Ku
#----------------------------------------------------------------
=begin
= copy.rb

== brief
�t�@�C���E�f�B���N�g���̃R�s�[

== since
2008-05-03 20:00:25

== author
HRYKY

== version
$Id: copy.rb 753 2010-06-13 03:03:03Z hryky $

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
#--------------------------------
=begin
--- copy
    �P��̃t�@�C���܂��̓f�B���N�g�����R�s�[
=end
#--------------------------------
def copy_file(source, destination, preserve, verbose, update)
  begin

    # �R�s�[�����f�B���N�g��
    if FileTest.directory?(source)

      # �X�V�Ȃ�
      if update

        # �R�s�[��f�B���N�g�����쐬
        FileUtils.mkdir_p(destination)

        pattern = "#{source}/**/*"

        # �R�s�[���f�B���N�g���𑖍�
        Dir.glob(pattern) { |file|

          # �t�@�C�����ċA�I�ɃR�s�[
          copy_file(
            file,
            destination + "/" + File.basename(file),
            preserve,
            verbose,
            update)
        }
        
      else
        # FileUtils.copy_entry(source, destination, preserve)
        FileUtils.cp_r(
          source, destination, {:verbose => verbose})
      end

      # �R�s�[�����t�@�C��
    else

      # �X�V�����ŃR�s�[�����Â���ΕԂ�
      return if update && !FileUtils.uptodate?(source, [destination])

      FileUtils.cp(
        source, destination,
        {:verbose => verbose, :preserve => preserve}
      )
      
    end
    
  rescue
    $stderr << "ERROR : copy " << source << " to " << destination << "\n"
    raise
  end
end

#----------------------------------------------------------------
=begin
== ������(execution)
=end
#----------------------------------------------------------------
if File.expand_path($0) == File.expand_path(__FILE__)

  option_parser = OptionParser.new

  verbose = nil
  preserve = nil
  update = nil

  # �ڍ׏o��
  option_parser.on("-v", "--verbose") { |boolean| verbose = boolean }

  # ��ԕێ�
  option_parser.on("-p", "--preserve") { |boolean| preserve = boolean }

  # �X�V(�R�s�[�����V�����������㏑��)
  option_parser.on("-u", "--update") { |boolean| update = boolean }

  # �I�v�V�������
  option_parser.order!(ARGV)

  if 2 > ARGV.size
    $stderr << "ERROR : source and destination are not specified.\n"
    exit 1
  end

  # �R�s�[���z����擾
  sources = ARGV[0...-1]

  # �R�s�[���̑��݂��m�F
  sources.each { |source|
    if !FileTest.exist?(source)
      $stderr << "ERROR : source file '#{source}' is not found.\n"
      exit 1
    end
  }

  # �R�s�[����擾
  destination = ARGV[-1]

  # �R�s�[�悪����
  if FileTest.exist?(destination)

    # �R�s�[�悪�f�B���N�g��
    if FileTest.directory?(destination)

      # �e�R�s�[�����f�B���N�g���փR�s�[
      sources.each { |source|
        copy_file(
          source,
          destination + "/" + File.basename(source),
          verbose,
          preserve,
          update
        )
      }

      # �R�s�[�悪�t�@�C��
    else

      # �R�s�[��������
      if 1 < sources.size
        $stderr << "ERROR : multiple files can't be copied to a destination file.\n"
        exit 1
      end

      # �t�@�C�����R�s�[
      copy_file(sources[0], destination, verbose, preserve, update)
    end

    # �R�s�[�悪���݂��Ȃ�
  else

    # �R�s�[�������� �܂��� �R�s�[�����f�B���N�g��
    if 1 < sources.size || FileTest.directory?(sources[0])
      FileUtils.mkdir_p(destination, {:verbose => verbose})

      # �e�R�s�[�����f�B���N�g���փR�s�[
      sources.each { |source|
        copy_file(
          source,
          destination + "/" + File.basename(source),
          verbose,
          preserve,
          update
        )
      }
      
      # �R�s�[�����P�� ���� �t�@�C��
    else
      FileUtils.mkdir_p(File.dirname(destination), {:verbose => verbose})

      # �t�@�C�����R�s�[
      copy_file(sources[0], destination, verbose, preserve, update)
    end
    
  end

end
