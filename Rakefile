require 'bundler/gem_tasks'
require 'rake/extensiontask'
require 'rake/testtask'

Rake::ExtensionTask.new 'foma' do |ext|
  ext.lib_dir = 'lib/foma'
end

Rake::TestTask.new(:test) do |t|
  t.libs << 'test'
  t.libs << 'lib'
  t.test_files = FileList['test/*_test.rb']
end

task default: %i[clobber compile test build]
