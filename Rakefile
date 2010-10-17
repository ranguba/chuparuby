# -*- coding: utf-8; mode: ruby -*-

require 'English'

require 'find'
require 'fileutils'
require 'rubygems'
require 'hoe'
require 'rake/extensiontask'

base_dir = File.join(File.dirname(__FILE__))
truncate_base_dir = Proc.new do |x|
  x.gsub(/^#{Regexp.escape(base_dir + File::SEPARATOR)}/, '')
end

chupa_ext_dir = File.join(base_dir, 'ext', 'chupa')
chupa_lib_dir = File.join(base_dir, 'lib')
$LOAD_PATH.unshift(chupa_ext_dir)
$LOAD_PATH.unshift(chupa_lib_dir)
ENV["RUBYLIB"] = "#{chupa_lib_dir}:#{chupa_ext_dir}:#{ENV['RUBYLIB']}"

def guess_chuparuby_version
  require 'chupatext'
  Chupa.bindings_version
end

manifest = File.join(base_dir, "Manifest.txt")
manifest_contents = []
base_dir_included_components = %w(AUTHORS COPYING ChangeLog GPL
                                  NEWS README.doc Rakefile
                                  extconf.rb pkg-config.rb)
excluded_components = %w(.cvsignore .gdb_history CVS depend Makefile pkg
                         .test-result .gitignore .git vendor)
excluded_suffixes = %w(.png .ps .pdf .o .so .a .txt .~ .log)
Find.find(base_dir) do |target|
  target = truncate_base_dir[target]
  components = target.split(File::SEPARATOR)
  if components.size == 1 and !File.directory?(target)
    next unless base_dir_included_components.include?(components[0])
  end
  Find.prune if (excluded_components - components) != excluded_components
  next if excluded_suffixes.include?(File.extname(target))
  manifest_contents << target if File.file?(target)
end

File.open(manifest, "w") do |f|
  f.puts manifest_contents.sort.join("\n")
end

# For Hoe's no user friendly default behavior. :<
File.open("README.txt", "w") {|file| file << "= Dummy README\n== XXX\n"}
FileUtils.cp("NEWS", "History.txt")
at_exit do
  FileUtils.rm_f("README.txt")
  FileUtils.rm_f("History.txt")
  FileUtils.rm_f(manifest)
end

ENV["VERSION"] ||= guess_chuparuby_version
version = ENV["VERSION"]
project = Hoe.spec('chupatext') do |project|
  project.version = version
  project.rubyforge_name = 'groonga'
  authors = File.join(base_dir, "AUTHORS")
  project.author = File.readlines(authors).collect do |line|
    if /\s*<[^<>]*>$/ =~ line
      $PREMATCH
    else
      nil
    end
  end.compact
  project.email = ['groonga-users-en@rubyforge.com',
                   'groonga-dev@lists.sourcefoge.jp']
  project.summary = 'Ruby bindings for ChupaText'
  project.url = 'http://groonga.rubyforge.org/'
  project.test_globs = []
  project.spec_extras = {
    :extensions => ['ext/chupa/extconf.rb'],
    :require_paths => ['lib'],
    :has_rdoc => false,
  }
  project.extra_dev_deps << ['pkg-config', '>= 0']
  platform = ENV["FORCE_PLATFORM"]
  project.spec_extras[:platform] = platform if platform
  news = File.join(base_dir, "NEWS")
  project.changes = File.read(news).gsub(/\n+^Release(?m:.*)/, '')
  project.description = 'Ruby bindings for ChupaText'
  project.need_tar = false
  project.remote_rdoc_dir = "doc"
end

project.spec.dependencies.delete_if {|dependency| dependency.name == "hoe"}

# fix Hoe's incorrect guess.
project.spec.executables.clear

task(:release).prerequisites.reject! {|name| name == "clean"}
task(:release_to_rubyforge).prerequisites.reject! {|name| name == "clean"}

# for releasing
task :dist => [:docs] do
  sh "./dist.sh", version
end