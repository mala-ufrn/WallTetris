# WALLTETRIS

Walltetris é um jogo desenvolvido para a disciplina de Computação Gráfica I do curso de Bacharelado em Ciências da Computação. O jogo foi desenvolvido em C++, fazendo uso da biblioteca gráfica OpenGL em sua versão 3.3. Seus principais objetivos são: demonstrar domínio de conceitos e técnicas como aplicação de matrizes para visualização e transformações geométricas, uso de texturas e iluminação. 

Mantendo as demais mecânicas do jogo TETRIS® original, foram removidos os limites horizontais, unindo os lados do campo, e auterada a sua forma de visualização, fazendo-o assemelhar-se com uma construção de 4 paredes, por isso o nome “Wall”tetris.

![Imagem da tela de jogo](https://github.com/mala-ufrn/WallTetris/.readme_imgs/screenshot01.png)

### DEPENDÊNCIAS:
####GLFW
```sudo apt-get install libglfw3-dev```

####Freetype2
```sudo apt-get install libfreetype6-dev```

####GLM
```sudo apt-get install libglm-dev```

####GLAD
Passo a passo de instalação:
1. Vá em https://glad.dav1d.de/
2. Em *API* mude gl para "version 3.3" ou mais novo
3. Em *Profile* mude para "Core"
4. Cheque se a checkbox "Generate a loader" está marcada
5. Aperte em "GENERATE"
6. Baixe o **glad.zip** gerado
<<<<<<< Updated upstream
7. Extraia e transfira a **glad/include/glad** para a para a pasta padrão do ubuntu:</br>```sudo mv glad/include/glad /usr/include/ -i```
=======
7. Extraia e transfira a pasta **glad/** do diretório **glad/include/** para a para o diretório **include/** do projeto.


>>>>>>> Stashed changes

## PARA COMPILAR E EXECURAR:
Na pasta raiz do projeto execute:</br>
  ```make```


## Autores

* **Hugo Oliveira** - *idealizer/developer* - [HugoTHO](https://github.com/HugoTHO)
* **Joel Felipe** - *developer* - [joelffg](https://github.com/joelffg)