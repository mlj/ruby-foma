# foma

[![Gem Version](https://badge.fury.io/rb/foma.svg)](http://badge.fury.io/rb/foma)
[![Build Status](https://secure.travis-ci.org/mlj/ruby-foma.svg?branch=master)](http://travis-ci.org/mlj/ruby-foma?branch=master)

foma is a wrapper for the FOMA finite state library.

This wrapper only provides functions for loading an FSM and for invoking the operations `apply up` and `apply down`.

Ruby 2.4 or higher required.

## Installation

```shell
gem install foma
```
or add the following line to your Gemfile

```ruby
gem 'foma'
```

and run `bundle install`.

If the foma headers and library are installed in a non-standard location, you
may have to specify the installation path, e.g

```shell
gem install foma -- --with-foma-include=$HOME/include --with-foma-lib=$HOME/lib
```

## Usage

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

## Development

The project is hosted on [GitHub](http://github.com/mlj/ruby-foma).

## License

MIT
