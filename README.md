<h1 id="top" align="center">DTP</h1>

<p align="center">
  <img alt="Github top language" src="https://img.shields.io/github/languages/top/SousaPedroso/dtp?color=56BEB8">

  <img alt="Github language count" src="https://img.shields.io/github/languages/count/SousaPedroso/dtp?color=56BEB8">

  <img alt="Repository size" src="https://img.shields.io/github/repo-size/SousaPedroso/dtp?color=56BEB8">

  <img alt="License" src="https://img.shields.io/github/license/SousaPedroso/dtp?color=56BEB8">

  <!-- <img alt="Github issues" src="https://img.shields.io/github/issues/{{YOUR_GITHUB_USERNAME}}/dtp?color=56BEB8" /> -->

  <!-- <img alt="Github forks" src="https://img.shields.io/github/forks/{{YOUR_GITHUB_USERNAME}}/dtp?color=56BEB8" /> -->

  <!-- <img alt="Github stars" src="https://img.shields.io/github/stars/{{YOUR_GITHUB_USERNAME}}/dtp?color=56BEB8" /> -->
</p>

<!-- Status -->

<!-- <h4 align="center"> 
	🚧  DTP 🚀 Under construction...  🚧
</h4> 

<hr> -->

<p align="center">
  <a href="#dart-about">About</a> &#xa0; | &#xa0; 
  <a href="#sparkles-features">Features</a> &#xa0; | &#xa0;
  <a href="#white_check_mark-requirements">Requirements</a> &#xa0; | &#xa0;
  <a href="#checkered_flag-starting">Starting</a> &#xa0; | &#xa0;
  <a href="#memo-license">License</a> &#xa0; | &#xa0;
  <a href="https://github.com/SousaPedroso" target="_blank">Author</a> &#xa0; | &#xa0;
  <a href="#book-acknowledgments">Acknowledgments</a>
</p>

<br>

## :dart: About ##


Proposed work on Artificial Intelligence by professor and Ph.D [Claudia Martins](http://lattes.cnpq.br/0252766947347684) to implement from scratch Decision Tree and Perceptron and compare the performance between those two ML algorithms through a small dataset.

Both Decision Tree and Perceptron had 100% of accuracy on [training data](data/sample.in). Modifying parameters can demonstrate different classifications on [new data](data/target.in) and due to not having the class for this data, any modification will depends on the target domain for choose which algorithm use.
## :sparkles: Features ##

:heavy_check_mark: Perceptron and Decision Tree adaptable to multiple features (considering first column as index and last one the target);\
:heavy_check_mark: Perceptron customizable;

## :white_check_mark: Requirements ##

Before starting :checkered_flag:, you need to have a compiler which supports c++17.

## :checkered_flag: Starting ##

```bash
# Clone this project
$ git clone https://github.com/SousaPedroso/dtp

# Access
$ cd dtp

# Compile files (Considering g++, change for your compiler)
$ g++ main.cpp Node.cpp DecisionTree.cpp Perceptron.cpp error.cpp encoder.cpp utils.cpp -o main -std=c++17

# Run the project
$ .\main

# Follow the instructions in the program
```

## :memo: License ##

This project is under license from MIT. For more details, see the [LICENSE](LICENSE) file.

## :book: Acknowledgments ##
[Claudia Martins](http://lattes.cnpq.br/0252766947347684)
[Mauro de Souza](https://github.com/maurodesouza/vscode-simple-readme)
&#xa0;

<a href="#top">Back to top</a>
