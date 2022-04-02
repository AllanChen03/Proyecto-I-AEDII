import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Conexion {

    BufferedReader lector = null;
    PrintWriter escritor = null;
    public Socket sockete;
    Thread principal = null;
    String mensaje_in = null;

    public Conexion() {
        Conectar();
    }

    public void Conectar() {
        principal = new Thread(new Runnable() {
            public void run() {
                try {
                    if (sockete == null) {
                        sockete = new Socket("192.168.0.103", 8080);
                        Leer();
                    }

                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
        principal.start();

    }

    public void Leer() {
        Thread leer_hilo = new Thread(new Runnable() {
            public void run() {

                try {
                    lector = new BufferedReader(new InputStreamReader(sockete.getInputStream()));
                    while (true) {
                        String mensaje = lector.readLine();
                        if (lector == null) {
                            System.out.println("NO se conecta");
                        } else {
                            System.out.println("Este es el mensaje: " + mensaje);
                        }
                    }

                } catch (Exception ex) {
                    ex.printStackTrace();

                }
            }

        });
        leer_hilo.start();

    }

    /**
     * Envia datos al servidor
     *
     * @param dato
     */
    public void Escribir(String dato) {

        try {
            escritor = new PrintWriter(sockete.getOutputStream(), true);
            escritor.println(dato);
            System.out.println(dato);
        } catch (Exception ex) {
            ex.printStackTrace();
        }

    }

    public static void main(String[] args) {

    }
}
