#include <iostream>
#include <iomanip>
#include <cmath> // para log y funciones matematicas
using namespace std;

// Declaracion de las funciones
long double f1(long double x); // f1(x) = x^2 * cos(x) - 2x
long double f2(long double x); // f2(x) = (6 - 2/x^2) * (e^(2+x)/4) + 1
long double f3(long double x); // f3(x) = x^3 - 3*sin(x^2) + 1
long double f4(long double x); // f4(x) = x^3 + 6x^2 + 9.4x + 2.5

// Prototipos de metodos
long double secante(long double p0, long double p1, long double (*f)(long double), int kmax, long double eps);
long double biseccion(long double a, long double b, long double (*f)(long double), int kmax, long double eps);

int main() {
    int opcion, metodo, kmax;
    long double p0, p1, a, b, eps, raiz;
    bool continuar = true;

    while (continuar) {
        // Menú de métodos
        cout << "Programa hecho por Garcia Reyes Arely Lizeth, Hernandez Barraza Alejandro y Lozano Perez Johan Andres\n";
        cout << "Seleccione el metodo para encontrar la raiz:\n";
        cout << "1. Metodo de la secante\n";
        cout << "2. Metodo de biseccion\n";
        cin >> metodo;

        // Menú de funciones
        cout << "Seleccione la funcion:\n";
        cout << "1. f(x) = x^2 * cos(x) - 2x\n";
        cout << "2. f(x) = (6 - 2/x^2) * (e^(2+x)/4) + 1\n";
        cout << "3. f(x) = x^3 - 3*sin(x^2) + 1\n";
        cout << "4. f(x) = x^3 + 6x^2 + 9.4x + 2.5\n";
        cin >> opcion;

        // Asignacion de funcion seleccionada
        long double (*f)(long double);
        switch (opcion) {
            case 1: f = f1; break;
            case 2: f = f2; break;
            case 3: f = f3; break;
            case 4: f = f4; break;
            default:
                cout << "Funcion no valida.\n";
                continue;
        }

        // Solicitud de parametros
        if (metodo == 1) { // Secante
            cout << "Ingrese el intervalo inicial (p0 y p1):\n";
            cin >> p0 >> p1;
            cout << "Ingrese la tolerancia de error (eps):\n";
            cin >> eps;
            cout << "Ingrese el maximo numero de iteraciones (kmax):\n";
            cin >> kmax;

            // Verificacion de entradas validas para la funcion seleccionada
            while (isnan(f(p0)) || isnan(f(p1))) {
                if (isnan(f(p0)))
                    cout << "La funcion no esta definida en " << p0 << endl;
                if (isnan(f(p1)))
                    cout << "La funcion no esta definida en " << p1 << endl;
                cout << "Ingrese nuevamente las aproximaciones iniciales p0, p1:\n";
                cin >> p0 >> p1;
            }

            // Metodo de la secante
            raiz = secante(p0, p1, f, kmax, eps);
            cout << "La ra z aproximada encontrada es: " << raiz << endl;

        } else if (metodo == 2) { // Biseccion
            cout << "Ingrese el intervalo (a y b):\n";
            cin >> a >> b;
            cout << "Ingrese la tolerancia de error (eps):\n";
            cin >> eps;
            cout << "Ingrese el maximo n mero de iteraciones (kmax):\n";
            cin >> kmax;

            // Verificacion de entradas validas para la funcion seleccionada
            while (isnan(f(a)) || isnan(f(b)) || f(a) * f(b) >= 0) {
                if (isnan(f(a)))
                    cout << "La funcion no esta definida en " << a << endl;
                if (isnan(f(b)))
                    cout << "La funcion no esta definida en " << b << endl;
                if (f(a) * f(b) >= 0)
                    cout << "La funcion debe tener diferentes signos en a y b." << endl;
                cout << "Ingrese nuevamente el intervalo a, b:\n";
                cin >> a >> b;
            }

            // Metodo de biseccion
            raiz = biseccion(a, b, f, kmax, eps);
            cout << "La raiz aproximada encontrada es: " << raiz << endl;
        } else {
            cout << "Metodo no implementado. Seleccione nuevamente.\n";
            continue;
        }

        // Preguntar si se desea otra raiz o regresar al menú 
        char respuesta;
        cout << "Desea buscar otra raiz con la misma funcion? (s/n): ";
        cin >> respuesta;
        if (respuesta == 'n' || respuesta == 'N') {
            cout << "Desea regresar al menos de funciones? (s/n): ";
            cin >> respuesta;
            if (respuesta == 'n' || respuesta == 'N') {
                continuar = false;
            }
        }
    }

    return 0;
}

// Definicion de funciones
long double f1(long double x) {
    return pow(x, 2) * cos(x) - 2 * x;
}

long double f2(long double x) {
    return (6 - 2 / pow(x, 2)) * (exp(2 + x) / 4) + 1;
}

long double f3(long double x) {
    return pow(x, 3) - 3 * sin(pow(x, 2)) + 1;
}

long double f4(long double x) {
    return pow(x, 3) + 6 * pow(x, 2) + 9.4 * x + 2.5;
}

// Metodo de la secante modificado
long double secante(long double p0, long double p1, long double (*f)(long double), int kmax, long double eps) {
    long double p, sec;
    int k = 2;

    cout << "k" << setw(15) << "x" << setw(22) << "f(x)\n";
    cout << 0 << setprecision(10) << setw(20) << p0 << setw(20) << f(p0) << endl;
    cout << 1 << setprecision(10) << setw(20) << p1 << setw(20) << f(p1) << endl;

    while ((k <= kmax) && (fabs(f(p1)) > eps)) {
        sec = (f(p1) - f(p0)) / (p1 - p0);
        p = p1 - f(p1) / sec;
        cout << k << setprecision(10) << setw(20) << p << setw(20) << f(p) << endl;
        p0 = p1;
        p1 = p;
        k++;
    }

    if (fabs(f(p1)) <= eps) 
        return p1;
    else {
        cout << "El metodo no converge en " << kmax << " pasos.\n";
        return p1;  // ultima aproximacion
    }
}

// Metodo de biseccion
long double biseccion(long double a, long double b, long double (*f)(long double), int kmax, long double eps) {
    long double c;
    int k = 0;

    cout << "k" << setw(15) << "a" << setw(15) << "b" << setw(20) << "c" << setw(22) << "f(c)\n";
    
    while (k < kmax) {
        c = (a + b) / 2; // Punto medio
        cout << k << setprecision(10) << setw(20) << a << setw(20) << b << setw(20) << c << setw(20) << f(c) << endl;

        // Verificar el signo de f(c)
        if (fabs(f(c)) <= eps) {
            return c; // Si f(c) es suficientemente pequeño
        }
        
        if (f(a) * f(c) < 0) {
            b = c; // La raiz esta en [a, c]
        } else {
            a = c; // La raiz esta en [c, b]
        }

        k++;
    }

    return c; // Retorna el ultimo c calculado
}

