import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Forca {

    
    public static void desenharForca(int tentativas) {
        String[] forcas = {
            "-----\n|   |\n    |\n    |\n    |\n    |\n", 
            "-----\n|   |\nO   |\n    |\n    |\n    |\n", 
            "-----\n|   |\nO   |\n|   |\n    |\n    |\n", 
            "-----\n|   |\nO   |\n|\\  |\n    |\n    |\n", 
            "-----\n|   |\nO   |\n|\\  |\n/   |\n    |\n", 
            "-----\n|   |\nO   |\n|\\  |\n/ \\ |\n    |\n", 
            "-----\n|   |\nO   |\n|\\  |\n/ \\ |\n    |\n"  
        };
        System.out.println(forcas[tentativas]);
    }

    
    public static void jogarForca() {
      
        List<String> palavras = Arrays.asList("Suits", "the walking dead", "doctor house");

        
        Random rand = new Random();
        String palavraSecreta = palavras.get(rand.nextInt(palavras.size()));
        
      
        char[] letrasDescobertas = new char[palavraSecreta.length()];
        Arrays.fill(letrasDescobertas, '_');
        List<Character> letrasUsadas = new ArrayList<>();
        int tentativas = 0;
        int maxTentativas = 6; 

        String tema = "Series"; 

        Scanner scanner = new Scanner(System.in);

        System.out.println("Bem-vindo ao Jogo da Forca!");
        System.out.println("O tema da palavra é: " + tema);
        System.out.println("A palavra tem " + palavraSecreta.length() + " letras.");

       
        while (tentativas < maxTentativas) {
            System.out.println("\nPalavra: " + String.valueOf(letrasDescobertas));
            System.out.println("Tentativas feitas: " + tentativas);
            System.out.println("Letras usadas: " + letrasUsadas);
            desenharForca(tentativas);

            System.out.println("\nVocê pode tentar adivinhar a palavra inteira ou digitar uma letra");
            System.out.print("Digite uma letra ou a palavra inteira (ou 'sair' para sair do jogo): ");
            String entrada = scanner.next().toLowerCase();

            
            if (entrada.equals("sair")) {
                System.out.println("Você escolheu sair do jogo. Até logo!");
                break;
            }

        
            if (entrada.length() > 1) {
                if (entrada.equals(palavraSecreta)) {
                    System.out.println("Parabéns! Você acertou a palavra: " + palavraSecreta);
                    break;
                } else {
                    System.out.println("A palavra está errada. Tente novamente.");
                    tentativas++;
                }
            } else {
              
                char letra = entrada.charAt(0);

               
                if (letrasUsadas.contains(letra)) {
                    System.out.println("Você já usou essa letra. Tente outra.");
                    continue;
                }

                
                if (Character.isLetter(letra)) {
                    letrasUsadas.add(letra);

                    
                    if (palavraSecreta.indexOf(letra) >= 0) {
                        System.out.println("Boa! A letra '" + letra + "' está na palavra.");
                    
                        for (int i = 0; i < palavraSecreta.length(); i++) {
                            if (palavraSecreta.charAt(i) == letra) {
                                letrasDescobertas[i] = letra;
                            }
                        }
                    } else {
                        System.out.println("A letra '" + letra + "' não está na palavra.");
                        tentativas++;
                    }

                    if (!new String(letrasDescobertas).contains("_")) {
                        System.out.println("\nParabéns! Você descobriu a palavra: " + palavraSecreta);
                        break;
                    }
                } else {
                    System.out.println("Por favor, digite uma letra válida.");
                }
            }
        }

        
        if (tentativas == maxTentativas) {
            desenharForca(tentativas);
            System.out.println("\nVocê perdeu! A palavra era: " + palavraSecreta);
        }

        scanner.close();
    }

    public static void main(String[] args) {
        
        jogarForca();
    }
}