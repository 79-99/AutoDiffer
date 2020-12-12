[![Build Status](https://travis-ci.com/79-99/cs107-FinalProject.svg?token=NY52fXtysbRAJ9UcMZek&branch=master)](https://travis-ci.com/79-99/cs107-FinalProject) [![codecov](https://codecov.io/gh/79-99/cs107-FinalProject/branch/master/graph/badge.svg?token=KJFBZT01H3)](https://codecov.io/gh/79-99/cs107-FinalProject)

### Group Number 4

Group Members
* Katrina Gonzalez - katrina_gonzalez@college.harvard.edu
* Chenguang Li - chenguang_li@fas.harvard.edu
* Michael Neuder - michaelneuder@g.harvard.edu

# Overview
Our software implements forward mode automatic differentiation (AD) in C++. Briefly, AD is a method of finding the derivatives of functions quickly and to machine precision. Our group's extension was to incorporate multithreading to improve performance. See the Introduction and Background section of our [documentation](docs/documentation.ipynb) for more information. 

For a video introduction and some demonstrations, see [this link](https://youtu.be/EvIuxCbVNGU).

Dependencies:
1. g++
2. CMake
3. Openmp (optional if you want to run the multithreaded AutoDiffer).

Fast install:

1. Clone this repo.
2. Run `bash config.sh` in the top level directory. This will build the project and run unit tests.
3. Include `AutoDiffer.hpp` to use the library. No linking is necessary, because this is a header only library.
4. Check out [examples README](examples/README.md) for example usage and demo Makefiles.

See [Documentation](docs/documentation.ipynb) for more details.

# Broader impact and inclusivity

* What are the potential broader impacts and implications of your software?


AD is a tool that can be applied in numerous branches of science and math. One of the most currently popular applications would be to speed up calculations for deep neural network training. Here we focus on issues in collecting or using large datasets, which is what the AD package would facilitate. 
Large datasets come with privacy, access, and data bias concerns. The first two relate to the datasets themselves. It is important to be aware, at every step of collection, of where data are coming from and how broadly available they are. If necessary, health data or other identifiable personal information must be properly anonymized. 
If privacy is a priority, then users of large datasets must respect the people providing their information. Otherwise, it would be preferable to have datasets be open-access for the sake of transparency in data science and research applications.

Another concern is that the larger NNs are, the more black-box-like they can become. Their inferences can be insidious depending on collection methods--for example, clinical data has historically been skewed toward white males. Even today, doctors are often less adept at recognizing symptoms of heart attacks in women because of how medical studies have prioritized studying disease presentation in males ("The Mounting Crisis in Women's Heart Health"). 
Due to data disparity, generalizations made by large NNs can perform poorly on female or minority populations. This means that even with the compute advantage that AD can provide, the data fed to a network must be carefully monitored to prevent harmful biases from data.

* How is your software inclusive to the broader community?

Our software is designed to be easy to use out-of-the-box. We have all of our code available on Github for anyone to clone and will look over contributions/pull requests as a team. We will take care to acknowledge our own implicit biases during review and try to reduce their effects on our decision-making.

We note that many people have reduced access to resources for learning C++, due to time constraints, language barriers, or overt or implicit discrimination in their educational system. 
To help mitigate such barriers, we include some resources: [Learn C++](https://www.learncpp.com/), [Cplusplus.com](https://www.cplusplus.com/), [edX resources](https://www.edx.org/learn/c-plus-plus). 
For non-native English speakers, there is a lot to be desired in terms of widely available educational resources for C++. Some steps in this direction, however, include subtitle options available for [Coursera](https://www.coursera.org/specializations/coding-for-everyone) classes or projects like [this one](https://github.com/akercheval/si) for Spanish-speaking students, which translates English keywords in Python or C++ to Spanish.

For broader support for underrepresented minorities in tech, [here](https://github.com/include-cpp/include) is a list of diversity and inclusion initiatives that specifically address issues in the C++ developers community.

Sources:

“The Mounting Crisis in Women's Heart Health.” Columbia University Department of Surgery, Columbia University Irving Medical Center, columbiasurgery.org/news/mounting-crisis-women-s-heart-health. 
