# O problema do caixeiro viajante

Um caixeiro viajante precisa visitar 10 cidades do interior de Pernambuco. Ele pede a um agente de busca que determine uma rota para sua visita tal que cada cidade só seja visitada uma única vez, e ele percorra o menor espaço possível (em Km). O agente de busca tem um mapa do estado, e portanto sabe as distâncias entre as cidades.

##### Formule e implemente este problema em termos de estado inicial, estado final, operadores e função de avaliação para Busca por melhoras iterativas com Hill- Climbing.

##### O operador considerado para gerar os filhos do estado corrente é permutar as cidades da rota atual duas a duas, e verificar em seguida se o caminho está conectado (segundo a tabela abaixo, que representa o mapa da questão). A cidade inicial deve ser mantida, uma vez que o caixeiro mora lá   A rota é fechada (ele volta à cidade de origem no final).