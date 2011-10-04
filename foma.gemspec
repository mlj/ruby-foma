# Generated by jeweler
# DO NOT EDIT THIS FILE DIRECTLY
# Instead, edit Jeweler::Tasks in Rakefile, and run 'rake gemspec'
# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = %q{foma}
  s.version = "0.1.0"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Marius L. J\303\270hndal"]
  s.date = %q{2011-10-05}
  s.description = %q{A wrapper for the FOMA finite state library}
  s.email = %q{mariuslj (at) ifi [dot] uio (dot) no}
  s.extra_rdoc_files = [
    "README.rdoc"
  ]
  s.files = [
    "CHANGELOG",
    "ext/foma.c",
    "foma.gemspec",
    "test/test_foma.rb"
  ]
  s.homepage = %q{http://github.com/mlj/ruby-foma}
  s.require_paths = ["lib"]
  s.rubyforge_project = %q{foma}
  s.rubygems_version = %q{1.3.7}
  s.summary = %q{FOMA finite state library interface}

  if s.respond_to? :specification_version then
    current_version = Gem::Specification::CURRENT_SPECIFICATION_VERSION
    s.specification_version = 3

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
    else
    end
  else
  end
end

