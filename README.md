# ruby-foma

ruby-foma is a wrapper for the FOMA finite state library.

The wrapper only provides fuctions for loading an FSM and for applying the
operations 'apply up' and 'apply down'.  But this is most likely all you will
need in an application...

Installation
------------

```shell
gem install foma
```
or add the following line to your Gemfile:
```ruby
gem 'foma'
```
and run `bundle install`.

If the foma headers and library are installed in a non-standard location, you
may have to specify the installation path:

```shell
gem install foma -- --with-foma-include=/some/where --with-foma-lib=/some/where
```

Usage
-----

```ruby
fsm = FOMA::FSM.new("fsm.bin")

fsm.apply_up("foo")
# => true

fsm.apply_down("bar")
# => true

fsm.apply_up("foo") do |d|
  puts d
end
```

Development
-----------

The project is hosted on github on http://github.com/mlj/ruby-foma.

License
-------

MIT