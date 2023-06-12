<h1> 
   <p align="center"> 
      Multi Layer Perceptron
      <br> <img src="src/resources/icons/a.ico" alt="Logo" width="140" height="140">
   </p>
</h1>
<p>
   Implementation of a basic multilayer perceptron using C++ without any external libraries.
   <br><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/0b/Qt_logo_2016.svg/2560px-Qt_logo_2016.svg.png" alt="Qt" align="center" height="30">
 framework is used for GUI, project is written according to MVC design pattern.
</p>
<h2>Features 🤯</h2>
<ul>
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
   <li>Learning on given training dataset using cross-validation
      <img src="materials/README/Training.png" alt="">
   <li>Testing trained model with built-in drawing field or by importing pre-drawn image 
      <img src="materials/README/Testing.png" alt="">
   <li>Testing trained model on testing dataset 
      <img src="materials/README/TestingInProgress.png" alt="">
</ul>
<h2>Installation ⚙️</h2>
<pre>
   <code>
   make install
   </code>
</pre>
<br><p>And that's it! Compiled application will be located in the <i>bin</i> directory. </p>
<p>On MacOS it will also be located in Launchpad for ease of use. </p>
<p>On Windows... Well, we are working on it! </p>
<h2>Requirements ☑️</h2>
<ul>
   <li> <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/1822px-ISO_C%2B%2B_Logo.svg.png" alt="Qt" align="center" height="36"> C++17
   <li> <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/0b/Qt_logo_2016.svg/2560px-Qt_logo_2016.svg.png" alt="Qt" align="center" height="30"> Qt6.5.0
</ul>
<h2>TODO 👨‍💻</h2>
<ul>
   <li> Support any dataset by using mapping
   <li> Change pen's color for different datasets 
   <li> Create both portable and installable version of application for Windows 
</ul>
<h2>Acknowledgements 🙇</h2>
<ul>
   <li> <a href="https://youtu.be/bW4dKxtUFpg">Dmitriy Korobchenko</a> for video explaining maths behind back propagation algorithm
</ul>
