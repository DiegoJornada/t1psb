Jogo da Senha
=====

Implementação do "Jogo da Senha" na plataforma LPC2378

O objetivo deste trabalho é praticar a programação com ênfase em software básico, através da implementação do conhecido "Jogo da Senha" na plataforma LPC2378.

O jogo consiste em adivinhar a senha entrada por outro jogador, em uma certa quantidade de tentativas. A cada tentativa, o sistema informa a quantidade de dígitos na posição correta e na posição incorreta. Ao final, se o jogador não adivinhar a senha, o sistema exibe a senha digitada.

O jogo deve oferecer 10 tentativas ao segundo jogador. A cada tentativa, o LCD deve mostrar o seu número (0-9), e novamente aguardar a entrada de uma senha. Como na entrada inicial, são usados os botões de 1 a 4 e o botão 5 para confirmar.
A seguir, até 4 LEDs serão usados para exibir a quantidade de dígitos na posição correta, e a quantidade de dígitos na posição incorreta. Isso deve ser feito da seguinte forma: cada LED piscante indica um dígito na posição incorreta, e cada LED aceso indica um dígito na posição correta. Veja que a posição dos LEDs não tem nada a ver com a posição do dígito, para dificultar o jogo.
Por exemplo, supondo que a senha introduzida no início foi 1985:

    Tentativa 1: jogador experimenta 2943
        1 dígito em posição correta (9), 0 em posição incorreta (2, 4 e 3 não fazem parte da senha): Acende o LED mais à esquerda.
    Tentativa 2: jogador experimenta 1957
        2 dígitos em posição correta (1 e 9), 1 em posição incorreta (5): Acende os dois LEDs mais à esquerda, pisca o terceiro LED.
    Tentativa 3: jogador experimenta 1985
        4 dígitos em posição correta, 0 em posição incorreta: Acende os quatro LEDs mais à esquerda.


Essa implementação não permite que a senha "Mestra" tenha dígitos repetidos

Jogo foi Apresentado em 2014-04-24 
