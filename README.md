<h1> 
   <p align="center"> 
      Multi Layer Perceptron
      <br> <img src="src/resources/icons/a.ico" alt="Logo" width="140" height="140">
   </p>
</h1>

Implementation of a basic multilayer perceptron using C++ without any external libraries. Qt framework is used for GUI, project is written according to MVC design pattern. The project is a part of the School 21 curriculum.

## Table of Contents

- [About](#about)
   - [Features](#features)
- [Getting Started](#getting-started)
   - [Prerequisites](#prerequisites)
   - [Installing](#installing)
- [Running the tests](#running-the-tests)
- [Usage](#usage)
- [Built Using](#built-using)
- [Authors](#authors)
- [Acknowledgements](#acknowledgements)
- [License](#license)

## About

This project is a basic implementation of a multilayer perceptron. It allows to train and test the model on a given dataset. The project is written in C++ without any external libraries. The GUI is implemented using the Qt framework. The project is written according to the MVC design pattern.

### Features

<ul>
   <li>Learning on given training dataset using cross-validation
      <img src="materials/README/Training.png" alt="">
   <li>Testing trained model with built-in drawing field or by importing pre-drawn image
      <img src="materials/README/Testing.png" alt="">
   <li>Configure model properties for training such as:
      <ul>
         <li>Perceptron implementation type
            <ul>
               <li>Matrix
               <li>Graph
            </ul>
         <li>Number of hidden layers
         <li>Number of neurons (units) per hidden layer
         <li>Learning rate
         <li>Activation Function
            <ul>
               <li>Sigmoid
               <li>Leaky ReLU
               <li>Linear
               <li>Bipolar Sigmoid
            </ul>
      </ul>
      <img src="materials/README/Config.png" alt="">
   <li>Import pretrained model
      <img src="materials/README/LoadingPretrained.png" alt="">
   <li>Testing trained model on testing dataset 
      <img src="materials/README/TestingInProgress.png" alt="">
</ul>

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

What things you need to install the software and how to install them.

```text
cmake >= 3.10
gcc >= 7.5.0
Qt >= 6.5.0
```

```bash
sudo apt-get install cmake
sudo apt-get install gcc
sudo apt-get install qt6-base-dev
```

### Installing

A step by step series of examples that tell you how to get a development env running.

Clone the repository.

```bash
git clone

cd MonitoringSystem
```

Run the Makefile with the following command:

```bash
make install
```

## Running the tests

Explain how to run the automated tests for this system.

```bash
make test
```

## Usage

To run the project, execute the following command:

```bash
./SimpleMLP
```

## Built Using

- [C++](https://en.cppreference.com/w/) - Programming language
- [CMake](https://cmake.org/) - Build system
- [Qt](https://doc.qt.io/qt-5/qtwidgets-index.html) - GUI framework
- [Google Test](https://google.github.io/googletest/) - Testing framework

## Authors

This project was developed by:

| <img src="https://avatars.githubusercontent.com/u/88089961?v=4" alt="drawing" width="50"/> |[LudwigAndreas](https://github.com/LudwigAndreas)|
| --- | --- |
| <img src="https://avatars.githubusercontent.com/u/57820208?s=60&v=4" alt="drawing" width="50"/> | [AndrefHub](https://github.com/AndrefHub) |

## Acknowledgements

- [School 21](https://21-school.ru/) - Educational institution.
- [Dmitriy Korobchenko](https://youtu.be/bW4dKxtUFpg) for video explaining maths behind back propagation algorithm.

## License

This project is licensed under the School 21 License - see the [LICENSE](LICENSE) file for details.
