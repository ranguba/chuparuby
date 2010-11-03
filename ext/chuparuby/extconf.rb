#!/usr/bin/env ruby

require 'pathname'
require 'English'
require 'mkmf'
require 'fileutils'

begin
  require 'pkg-config'
rescue LoadError
  require 'rubygems'
  require 'pkg-config'
end

checking_for(checking_message("GCC")) do
  if macro_defined?("__GNUC__", "")
    $CFLAGS += ' -Wall'
    true
  else
    false
  end
end

package = "chupatext"
module_name = "chupatext"
major, minor, micro = 0, 4, 0

base_dir = Pathname(__FILE__).dirname.parent.parent
checking_for(checking_message("Win32 OS")) do
  case RUBY_PLATFORM
  when /cygwin|mingw|mswin32/
    $defs << "-DRUBY_CHUPA_PLATFORM_WIN32"
    import_library_name = "libruby-#{module_name}.a"
    $DLDFLAGS << " -Wl,--out-implib=#{import_library_name}"
    $cleanfiles << import_library_name
    binary_base_dir = base_dir + "vendor" + "local"
    $CFLAGS += " -I#{binary_base_dir}/include"
    pkg_config_dir = binary_base_dir + "lib" + "pkgconfig"
    PKGConfig.add_path(pkg_config_dir.to_s)
    PKGConfig.set_override_variable("prefix", binary_base_dir.to_s)
    true
  else
    false
  end
end

PKGConfig.have_package(package, major, minor, micro) or exit 1

$defs << "-DRB_CHUPA_COMPILATION"

create_makefile(module_name)
