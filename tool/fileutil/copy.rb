#! ruby -Ku
#----------------------------------------------------------------
=begin
= copy.rb

== brief
ファイル・ディレクトリのコピー

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
== クラス(class definition)
=end
#----------------------------------------------------------------

#----------------------------------------------------------------
=begin
== メソッド(method definition)
=end
#----------------------------------------------------------------
#--------------------------------
=begin
--- copy
    単一のファイルまたはディレクトリをコピー
=end
#--------------------------------
def copy_file(source, destination, preserve, verbose, update)
  begin

    # コピー元がディレクトリ
    if FileTest.directory?(source)

      # 更新なら
      if update

        # コピー先ディレクトリを作成
        FileUtils.mkdir_p(destination)

        pattern = "#{source}/**/*"

        # コピー元ディレクトリを走査
        Dir.glob(pattern) { |file|

          # ファイルを再帰的にコピー
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

      # コピー元がファイル
    else

      # 更新処理でコピー元が古ければ返る
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
== 実処理(execution)
=end
#----------------------------------------------------------------
if File.expand_path($0) == File.expand_path(__FILE__)

  option_parser = OptionParser.new

  verbose = nil
  preserve = nil
  update = nil

  # 詳細出力
  option_parser.on("-v", "--verbose") { |boolean| verbose = boolean }

  # 状態保持
  option_parser.on("-p", "--preserve") { |boolean| preserve = boolean }

  # 更新(コピー元が新しい時だけ上書き)
  option_parser.on("-u", "--update") { |boolean| update = boolean }

  # オプション解析
  option_parser.order!(ARGV)

  if 2 > ARGV.size
    $stderr << "ERROR : source and destination are not specified.\n"
    exit 1
  end

  # コピー元配列を取得
  sources = ARGV[0...-1]

  # コピー元の存在を確認
  sources.each { |source|
    if !FileTest.exist?(source)
      $stderr << "ERROR : source file '#{source}' is not found.\n"
      exit 1
    end
  }

  # コピー先を取得
  destination = ARGV[-1]

  # コピー先が存在
  if FileTest.exist?(destination)

    # コピー先がディレクトリ
    if FileTest.directory?(destination)

      # 各コピー元をディレクトリへコピー
      sources.each { |source|
        copy_file(
          source,
          destination + "/" + File.basename(source),
          verbose,
          preserve,
          update
        )
      }

      # コピー先がファイル
    else

      # コピー元が複数
      if 1 < sources.size
        $stderr << "ERROR : multiple files can't be copied to a destination file.\n"
        exit 1
      end

      # ファイルをコピー
      copy_file(sources[0], destination, verbose, preserve, update)
    end

    # コピー先が存在しない
  else

    # コピー元が複数 または コピー元がディレクトリ
    if 1 < sources.size || FileTest.directory?(sources[0])
      FileUtils.mkdir_p(destination, {:verbose => verbose})

      # 各コピー元をディレクトリへコピー
      sources.each { |source|
        copy_file(
          source,
          destination + "/" + File.basename(source),
          verbose,
          preserve,
          update
        )
      }
      
      # コピー元が単数 かつ ファイル
    else
      FileUtils.mkdir_p(File.dirname(destination), {:verbose => verbose})

      # ファイルをコピー
      copy_file(sources[0], destination, verbose, preserve, update)
    end
    
  end

end
