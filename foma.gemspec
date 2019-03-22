# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'foma/version'

Gem::Specification.new do |spec|
  spec.name          = "foma"
  spec.version       = FOMA::VERSION
  spec.authors       = ["Marius L. Jøhndal"]
  spec.email         = ["mariuslj@ifi.uio.no"]
  spec.summary       = %q{FOMA finite state library interface}
  spec.description   = %q{A wrapper for the FOMA finite state library}
  spec.homepage      = "http://github.com/mlj/ruby-foma"
  spec.license       = 'MIT'

  spec.files         = Dir["{ext,lib,test}/**/*"] + %w(README.md LICENSE)
  spec.require_paths = ["ext", "lib"]
  spec.extensions    = ["ext/foma/extconf.rb"]

  spec.required_ruby_version = '>= 2.2'

  spec.add_development_dependency 'bundler'
  spec.add_development_dependency 'rake', '~> 12.0'
  spec.add_development_dependency 'rake-compiler'
  spec.add_development_dependency 'minitest'
end
