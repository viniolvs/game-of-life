# Implementação Paralela

- Dividir a matriz em blocos
  - Cada thread modificará apenas seu bloco porém terá acesso a interseção com blocos adjacentes para aplicar corretamente a regra do jogo nas bordas do bloco
- Todas as threads devem terminar seus blocos antes da geração avançar
