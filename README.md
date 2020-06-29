# Image-Compressing-System

_This is a program developed to compress PGM-format images using the DCT (Discrete Cosine Transform) and the Huffman algorithm, in which the user can select the rate of compression of a given PGM image resulting in another PGM image after the DCT and Huffman process, having a 15% loss on the image weight at **maximal compresison**, a 12% loss at **normal compression** and finally a 10% loss at **minimun compression**_

To excecute the program it's only needed to run the "finalDEM.C" file.

## Built with
* C
## Running restrictions
* Linux: Works perfectly and all the processes of the image compression are executed as expected.
* MacOS: The DCT and Huffman algorithm create a new image file very similar to the original but with more gery-ish colors (brighter).
* Windows: The PGM reader couldn't read properly the image so the other processes coulsn't work.
## Credit
Final project for the subjects "Fundamentos y Estructuras de Programacion" and "Laboratorio de Programacion", developed in C++ and C at Pontificia Universidad Javeriana Cali, Colombia, 2016.
## Authors
* **Diego F. Galarza** - *Programming, Huffman and truncate implementation* - [diegogalarza](https://github.com/diegogalarza)
* **Maria P. Carrero** - *Programming, DCT implementation* - [mariapcarrero](https://github.com/mariapcarrero)
* **Enrique J. París** - *Programming, PGM reader implementation* - [EnriqueParis](https://github.com/EnriqueParis)
