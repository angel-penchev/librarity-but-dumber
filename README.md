<div>
  <h1 align="center">
    Librarity <i>(but dumber)</i>
  </h1>
  <p align="center">
    Command-line software solution for storing, organizing and accessing books.<br />
    <sub>Semester project #1 for the object oriented programming (OOP) course in Faculty of mathematics and informatics (FMI) Computer science's first curriculum.</sub>
  </p>
</div>

<div align="center">
  <a href="https://wakatime.com/@angel_penchev/projects/pztbnlucqg?start=2022-05-02&end=2022-05-15">
    <img src="https://wakatime.com/badge/user/0358f049-a6ea-4f46-9958-af19c371dc19/project/8b12fe87-07d6-4e37-a569-9a7811f6539e.svg?style=flat-square" alt="wakatime" />
  </a>
  <a href="https://github.com/angel-penchev/librarity-but-dumber/actions/workflows/test.yml">
    <img src="https://img.shields.io/github/workflow/status/angel-penchev/librarity-but-dumber/Test?label=tests&style=flat-square" alt="tests">
  </a>
  <a href="https://github.com/angel-penchev/librarity-but-dumber/releases">
    <img src="https://img.shields.io/github/v/release/angel-penchev/librarity-but-dumber?style=flat-square"alt="release>
  </a>
  <a href="LICENSE">
    <img src="https://img.shields.io/github/license/angel-penchev/librarity-but-dumber?style=flat-square" alt="license" />
  </a>
</div>


## Documentation
Latest version of the project documentation is available at [docs/documentation.pdf](docs/documentation.pdf). Doxygen documentaion is also available [here](https://codedocs.xyz/angel-penchev/librarity-but-dumber/).


## Setup
1. Clone the project repository.
```
git clone https://github.com/angel-penchev/librarity-but-dumber
cd librarity-but-dumber
```

2. Configure and build project.

To compile the project using make, simply run the following:
```
make
```

or you want to manually configure and build the project, run:
```
# Create cmake configuration
cmake -S. -Bcmake-build-debug -DCMAKE_BUILD_TYPE=Debug~

# Build project
cmake --build cmake-build-debug --config Debug
```

3. You're ready to go!

To start the application simply run:
```
make run
```
or
```
./cmake-build-debug/librarity_but_dumber_run
```

To run all application tests type:
```
make tests
```
or
```
cd cmake-build-debug
ctest --test-dir -C Debug --output-on-failure --verbose
```


## FAQ

**Isn't this way too over-engineered?**

YES.


**Is it spell checked at all?**
no... 😢


## Contributions
1. Fork it (<https://github.com/angel-penchev/librarity-but-dumber/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -a`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
6. Upon review it will be merged.


## License
Distributed under the BSD-3 Cause license. See [LICENSE](LICENSE) for more information.

