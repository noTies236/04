*April 27, 2026*

<img width="1915" height="1001" alt="Screenshot_48" src="https://github.com/user-attachments/assets/0b73964a-2039-418b-9bcb-a3d8c36bf376" />

In this project, the GLFW and glad libraries are used. I downloaded the libraries and kept them in a separate folder at the root of my computer. When I run the project everything works fine, because I configured my solution to find the folders using an absolute path. See how my solution is referencing the libraries:

<img width="1002" height="114" alt="Screenshot_50" src="https://github.com/user-attachments/assets/38e43217-667f-4aa2-aa62-a4cfba8671b6" />

But there is a small detail here — if someone clones my project and tries to run the program, it won't work. This happens because the libraries are saved locally on my PC and my project is using the full path to access the files. An absolute path always starts from the root.

My absolute path looks like this: C:\Users\wallyson\source\repos\04\lib\include\includeGlad — but on your machine, the repos folder might not even exist.

To solve this, we are going to use something called a vendor folder. The idea behind vendor is the following: we go into our project and create a folder called vendor(in my case i use the name lib), and inside it we place all the libraries the project needs. This way we eliminate the need for absolute paths in our solution and switch to using relative paths instead.
<img width="1001" height="140" alt="Screenshot_49" src="https://github.com/user-attachments/assets/320b4b3f-88d3-43d2-9b04-d6197fefc48f" />

*XX/XX/2025*
![image](https://github.com/user-attachments/assets/66bb1ac1-e13d-47cd-8b97-28a1eb2e6366)
