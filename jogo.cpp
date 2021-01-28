#include <valarray>
#include "jogo.h"
#include "memoria.h"

Jogo::Jogo(Mapa &t) : nome(""), ultimo(""), nTurnos(1), nFase(1), unidadeMilitar(0), armazem(0), cofre(0), fatorSorte(0), drones(false), misseis(false), defesa(false), bolsa(false), banco(false), recolha(false), compraM(false), compraT(false)
{
    d = &t;
}

Jogo::Jogo()
{
}

Jogo::Jogo(const Jogo &outro)
{
    *this = outro;
}

Jogo::~Jogo()
{
}

Jogo *Jogo::comandosJ(string comando, Memoria &m)
{
    istringstream iss(comando);
    string cmd;
    iss >> cmd;
    if (cmd == "carrega")
    {
        if (iss >> cmd)
            carregaC(cmd, m);
        else
            aviso("[AVISO] carrega <ficheiro> [AVISO]");
    }
    else if (cmd == "grava")
    {
        if (iss >> cmd)
        {
            nome = cmd;
            if (!m.verificaN(nome))
            {
                m.grava(new Jogo(*this));
                aviso("[AVISO] JOGO GRAVADO [AVISO]");
            }
            else
                erro("[ERRO] JOGO JA GRAVADO COM ESTE NOME [ERRO]");
        }
        else
            aviso("[AVISO] grava <nome> [AVISO]");
    }
    else if (cmd == "ativa")
    {
        if (iss >> cmd)
        {
            Jogo *c;
            if ((c = m.ativa(cmd)) != nullptr)
            {
                aviso("[AVISO] JOGO ATIVADO [AVISO]");
                return c;
            }
            else
            {
                erro("[ERRO] JOGO NAO ENCONTRADO [ERRO]");
                cout << "Jogos disponiveis:  " << m.obtemStringJogos() << endl;
            }
        }
        else
            aviso("[AVISO] ativa <nome> [AVISO]");
    }
    else if (cmd == "apaga")
    {
        if (iss >> cmd)
        {
            if (m.apaga(cmd))
                aviso("[AVISO] JOGO APAGADO [AVISO]");
            else
            {
                erro("[ERRO] JOGO NAO ENCONTRADO [ERRO]");
                cout << "Jogos disponiveis:  " << m.obtemStringJogos() << endl;
            }
        }
        else
            aviso("[AVISO] apaga <nome> [AVISO]");
    }
    else if (cmd == "fevento")
    {
        if (iss >> cmd)
        {
            fevento(cmd);
        }
        else
            erro("[ERRO] fevento <nome-evento> [ERRO]");
    }
    else if (cmd == "modifica")
    {
        int i;
        if (iss >> cmd && cmd == "ouro")
        {
            if (iss >> i)
                adicionaOuro(i);
            else
                erro("[ERRO] Valor inválido [ERRO]");
        }
        else if (cmd == "prod")
        {
            if (iss >> i)
                adicionaProd(i);
            else
                erro("[ERRO] Valor inválido [ERRO]");
        }
        else
            erro("[ERRO] modifica <ouro|prod> N [ERRO]");
    }
    else if (cmd == "toma")
    {
        if (iss >> cmd && cmd == "terr")
        {
            if (iss >> cmd)
                tomaTerr(cmd);
            else
                erro("[ERRO] NOME INVALIDO [ERRO]");
        }
        else if (cmd == "tec")
        {
            if (iss >> cmd)
                tomaTec(cmd);
            else
                erro("[ERRO] NOME INVALIDO [ERRO]");
        }
        else
            erro("[ERRO] toma <terr|tec> nome [ERRO]");
    }
    else if (cmd == "lista")
    {
        if (iss >> cmd)
        {
            cout << d->obtemTerritorio(cmd, nTurnos);
        }
        else
            cout << lista();
    }
    else if (cmd == "limpa")
        limpa();
    else
        switch (nFase)
        {
        case 1:
            if (!fase1(comando))
                break;
            else if (!bolsa)
            {
                cout << "Fase 2" << endl;
                aviso("[AVISO] RECOLHA AUTOMATICA DE PRODUTOS - BOLSA AINDA NAO ADQUIRIDA [AVISO]");
            }
            else
                break;
        case 2:
            fase2(comando);
            break;
        case 3:
            if (!fase3(comando))
                break;
        case 4:
            cout << "Fase 4" << endl;
            fase4();
            nTurnos++;
            break;
        }
    return nullptr;
}

bool Jogo::fase1(string comando)
{
    istringstream iss(comando);
    int i;
    string msg;
    string cmd[2] = {"conquista", "passa"};
    iss >> msg;
    for (i = 0; cmd[i] != msg; ++i)
        ;

    switch (i)
    {
    case 0:
        if (iss >> msg)
        {
            if (verificaConquista(msg))
                return true;
        }
        else
        {
            erro("[ERRO] conquista <nome> [ERRO]");
        }
        break;
    case 1:
        ++nFase;
        aviso("[AVISO] PASSOU A JOGADA [AVISO]");
        return true;
        break;
    default:
        cout << avisoInvalido(msg);
        break;
    }
    return false;
}

void Jogo::fase2(string comando)
{
    if (!recolha)
        recolhe();
    if (bolsa)
    {
        recolha = true;
        troca(comando);
    }
    else
    {
        ++nFase;
    }
}

bool Jogo::fase3(string comando)
{
    istringstream iss(comando);
    int i;
    string msg;
    string cmd[4] = {"maismilitar", "adquire", "passa"};
    iss >> msg;
    for (i = 0; cmd[i] != msg; ++i)
        ;

    switch (i)
    {
    case 0:
        if (!compraM)
            adquireMilitar();
        else if (compraM)
            aviso("[AVISO] JA ADQUIRIU UMA UNIDADE MILITAR NESTA FASE [AVISO]");
        break;
    case 1:
        if (iss >> msg)
        {
            if (contaTec())
            {
                aviso("[AVISO] TODAS AS TECNOLOGIAS JA ADQUIRIDAS [AVISO]");
                compraT = true;
            }
            else if (!compraT)
            {
                if (compraTecnologias(msg))
                    compraT = true;
            }
            else if (compraT)
                aviso("[AVISO] JA ADQUIRIU UMA TECNOLOGIA NESTA FASE [AVISO]");
        }
        else
            erro("[ERRO] adquire <tipo> [ERRO]");
        break;
    case 2:
        ++nFase;
        aviso("[AVISO] PASSOU A JOGADA [AVISO]");
        compraM = false;
        compraT = false;
        return true;
        break;
    default:
        cout << avisoInvalido(msg);
        break;
    }
    if (compraT && compraM)
    {
        ++nFase;
        compraM = false;
        compraT = false;
        return true;
    }
    return false;
}

void Jogo::fase4()
{
    switch (rand() % 4)
    {
    case 0:
        ultimo = "recurso";
        recurso();
        break;
    case 1:
        ultimo = "invasao";
        invasao();
        break;
    case 2:
        ultimo = "alianca";
        alianca();
        break;
    case 3:
        ultimo = "";
        aviso("[AVISO] SEM EVENTO [AVISO]");
        break;
    }
    nFase = 1;
}

int Jogo::conquista(Territorio *p)
{
    fatorSorte = rand() % 6 + 1; // Número aleatório entre 1 - 6
    int x = fatorSorte + unidadeMilitar;
    bool aux;
    if ((p->getNome().find("pescaria") == 0) || (p->getNome().find("refugio") == 0))
    {
        if (verifica())
            aux = true;
        else
        {
            aux = false;
            aviso("[AVISO] NAO SE ENCONTRA NAS CONDIÇOES NECESSARIAS PARA CONQUISTAR ESTE TERRITORIO [AVISO]");
            return 2;
        }
    }
    else
        aux = true;
    if (x >= p->getResistencia() && aux == true)
        return 1;
    else
        return 0;
}

bool Jogo::verifica()
{
    if (d->totalI() >= 5 && misseis == true)
        return true;
    else
        return false;
}

bool Jogo::verificaConquista(string nome)
{
    Territorio *p;
    if ((p = d->encontra(nome)) != nullptr)
    {
        int x = conquista(p);
        if (x == 0)
        {
            d->adicionaI(p);          // Acrescenta ao império
            d->removeT(p->getNome()); //Remove do mundo
            aviso("[AVISO] CONQUISTA COM SUCESSO [AVISO]");
            ++nFase;
            return true;
        }
        else if (x == 1)
        {
            if (unidadeMilitar > 0)
                --unidadeMilitar;
            aviso("[AVISO] FALHA NA CONQUISTA [AVISO]");
            ++nFase;
            return true;
        }
    }
    else
    {
        erro("[ERRO] NOME NAO ENCONTRADO [ERRO]");
        cout << d->obtemStringMundo(nTurnos);
    }
    return false;
}

void Jogo::recolhe()
{
    cofre += d->obtemOuroGerado(nTurnos);
    armazem += d->obtemProdutoGerado(nTurnos);
    if (cofre > obtemLimiteC())
        cofre = obtemLimiteC();
    if (armazem > obtemLimiteA())
        armazem = obtemLimiteA();
}

void Jogo::troca(string comando)
{
    istringstream iss(comando);
    int i;
    string msg;
    string cmd[3] = {"maisouro", "maisprod", "passa"};
    iss >> msg;
    for (i = 0; cmd[i] != msg; ++i)
        ;

    switch (i)
    {
    case 0:
        maisOuro();
        break;
    case 1:
        maisProdutos();
        break;
    case 2:
        ++nFase;
        recolha = false;
        aviso("[AVISO] PASSOU A JOGADA [AVISO]");
        break;
    default:
        cout << avisoInvalido(msg);
        break;
    }
}

void Jogo::maisOuro()
{
    if (armazem >= 2)
    {
        if (cofre < obtemLimiteC())
        {
            armazem -= 2;
            ++cofre;
            ++nFase;
            recolha = false;
            aviso("[AVISO] COMPRA DE OURO COM SUCESSO [AVISO]");
        }
        else
            aviso("[AVISO] NAO TEM CAPACIDADE SUFICIENTE [AVISO]");
    }
    else
        aviso("[AVISO] NAO TEM PRODUTOS SUFICIENTES [AVISO]");
}

void Jogo::maisProdutos()
{
    if (cofre >= 2)
    {
        if (armazem < obtemLimiteA())
        {
            cofre -= 2;
            ++armazem;
            ++nFase;
            recolha = false;
            aviso("[AVISO] COMPRA DE PRODUTOS COM SUCESSO [AVISO]");
        }
        else
            aviso("[AVISO] NAO TEM CAPACIDADE SUFICIENTE [AVISO]");
    }
    else
        aviso("[AVISO] NAO TEM OURO SUFICIENTES [AVISO]");
}

void Jogo::adquireMilitar()
{
    if (unidadeMilitar < obtemLimiteUM())
    {
        if (armazem >= 1 && cofre >= 1)
        {
            compraMilitar();
            compraM = true;
        }
        else
            erro("[ERRO] RECURSOS INSUFICIENTES [ERRO]");
    }
    else
        erro("[ERRO] LIMITE MILITAR ATINGIDO [ERRO]");
}

void Jogo::compraMilitar()
{
    ++unidadeMilitar;
    --armazem; //Produtos
    --cofre;   //Ouro
    cout << "OURO: " << cofre << endl;
    cout << "PRODUTOS: " << armazem << endl;
    cout << "UNIDADES MILITAR: " << unidadeMilitar << endl;
}

bool Jogo::compraTecnologias(string nome)
{
    int i;
    string cmd[5] = {"drones", "misseis", "defesa", "bolsa", "banco"};
    for (i = 0; i < 5 && cmd[i] != nome; ++i)
        ;

    switch (i)
    {
    case 0:
        if (cofre >= 3 && !(drones))
        {
            cofre -= 3;
            drones = true;
            aviso("[AVISO] DRONES MILITARES ADQUIRIDOS COM SUCESSO [AVISO]");
            return true;
        }
        else if (drones)
            aviso("[AVISO] DRONES JA ADQUIRIDOS [AVISO]");
        else
            aviso("[AVISO] OURO INSUFICIENTE [AVISO]");
        break;
    case 1:
        if (cofre >= 4 && !(misseis))
        {
            cofre -= 4;
            misseis = true;
            aviso("[AVISO] MISSEIS TELEGUIADOS ADQUIRIDOS COM SUCESSO [AVISO]");
            return true;
        }
        else if (drones)
            aviso("[AVISO] MISSEIS JA ADQUIRIDOS [AVISO]");
        else
            aviso("[AVISO] OURO INSUFICIENTE [AVISO]");
        break;
    case 2:
        if (cofre >= 4 && !(defesa))
        {
            cofre -= 4;
            defesa = true;
            aviso("[AVISO] DEFESAS TERRITORIAIS ADQUIRIDOS COM SUCESSO [AVISO]");
            return true;
        }
        else if (defesa)
            aviso("[AVISO] DEFESA JA ADQUIRIDA [AVISO]");
        else
            aviso("[AVISO] OURO INSUFICIENTE [AVISO]");
        break;
    case 3:
        if (cofre >= 2 && !(bolsa))
        {
            cofre -= 2;
            bolsa = true;
            aviso("[AVISO] BOLSA DE VALORES ADQUIRIDA COM SUCESSO [AVISO]");
            return true;
        }
        else if (bolsa)
            aviso("[AVISO] BOLSA JA ADQUIRIDA [AVISO]");
        else
            aviso("[AVISO] OURO INSUFICIENTE [AVISO]");
        break;
    case 4:
        if (cofre >= 3 && !(banco))
        {
            cofre -= 3;
            banco = true;
            aviso("[AVISO] BANCO CENTRAL ADQUIRIDO COM SUCESSO [AVISO]");
            return true;
        }
        else if (banco)
            aviso("[AVISO] BANCO JA ADQUIRIDO [AVISO]");
        else
            aviso("[AVISO] OURO INSUFICIENTE [AVISO]");
        break;
    default:
        erro("[ERRO] TECNOLOGIA INEXISTENTE [ERRO]");
        cout << "Lista: 'drones', 'misseis', 'defesa', 'bolsa', 'banco'" << endl;
        break;
    }
    return false;
}

void Jogo::adicionaOuro(int total)
{
    cofre = total;
    if (cofre > obtemLimiteC())
        cofre = obtemLimiteC();
    else if (cofre < 0)
    {
        cout << "VALOR NEGATIVO" << endl;
        cofre = 0;
    }
    cout << "OURO: " << cofre << endl;
}

void Jogo::adicionaProd(int total)
{
    armazem = total;
    if (armazem > obtemLimiteA())
        armazem = obtemLimiteA();
    else if (armazem < 0)
    {
        cout << "VALOR NEGATIVO" << endl;
        armazem = 0;
    }
    cout << "PRODUTOS: " << armazem << endl;
}

void Jogo::fevento(string evento)
{
    int i;
    string eventos[3] = {"recurso", "invasao", "alianca"};
    for (i = 0; eventos[i] != evento; ++i)
        ;
    switch (i)
    {
    case 0:
        ultimo = "recurso";
        recurso();
        break;
    case 1:
        ultimo = "invasao";
        invasao();
        break;
    case 2:
        ultimo = "alianca";
        alianca();
        break;
    default:
        erro("[ERRO] EVENTO INEXISTENTE [ERRO]");
        cout << "Lista: 'recurso', 'invasao', 'alianca'" << endl;
    }
}

void Jogo::recurso()
{
    if (obtemAno() == 1 && armazem < obtemLimiteA())
    {
        ++armazem;
        aviso("[AVISO] PRODUTO ADICIONADO [AVISO]");
    }
    else if (obtemAno() == 2 && cofre < obtemLimiteC())
    {
        ++cofre;
        aviso("[AVISO] OURO ADICIONADO [AVISO]");
    }
}

void Jogo::invasao()
{
    Territorio *p;
    p = d->obtemUltimo();
    fatorSorte = rand() % 6 + 1;

    if (obtemAno() == 1)
        defesaI((fatorSorte + 2), p);
    else
        defesaI((fatorSorte + 3), p);
}

void Jogo::defesaI(int vAtaque, Territorio *p)
{
    int x = (defesa == false) ? p->getResistencia() : p->getResistencia() + 1;
    if (x < vAtaque)
    {
        d->removeI();
        d->adicionaT(p);
        aviso("[AVISO] TERRITORIO PERDIDO [AVISO]");
    }
    else
        aviso("[AVISO] DEFESA BEM SUCEDIDA [AVISO]");
}

void Jogo::alianca()
{
    if (unidadeMilitar < obtemLimiteUM())
    {
        ++unidadeMilitar;
        aviso("[AVISO] ADICIONADA UNIDADE MILITAR [AVISO]");
    }
    else
        aviso("[AVISO] LIMITE DE UNIDADES MILITARES ATINGIDO [AVISO]");
}

void Jogo::tomaTerr(string msg)
{
    Territorio *p;
    if ((p = d->encontra(msg)) != nullptr)
    {
        d->adicionaI(p);
        d->removeT(p->getNome());
        cout << "COMANDO TOMA CONCLUIDO" << endl;
    }
    else
    {
        erro("[ERRO] NOME NAO ENCONTRADO [ERRO]");
        cout << d->obtemStringMundo(nTurnos);
    }
}

void Jogo::tomaTec(string msg)
{
    int i;
    string cmd[5] = {"drones", "misseis", "defesa", "bolsa", "banco"};
    for (i = 0; i < 5 && cmd[i] != msg; ++i)
        ;

    switch (i)
    {
    case 0:
        drones = true;
        aviso("[AVISO] DRONES ADQUIRIDOS [AVISO]");
        break;
    case 1:
        misseis = true;
        aviso("[AVISO] MISSEIS ADQUIRIDOS [AVISO]");
        break;
    case 2:
        defesa = true;
        aviso("[AVISO] DEFESA ADQUIRIDA [AVISO]");
        break;
    case 3:
        bolsa = true;
        aviso("[AVISO] BOLSA ADQUIRIDA [AVISO]");
        break;
    case 4:
        banco = true;
        aviso("[AVISO] BANCO ADQUIRIDO [AVISO]");
        break;
    default:
        erro("[ERRO] TECNOLOGIA INEXISTENTE [ERRO]");
        cout << "Lista: 'drones', 'misseis', 'defesa', 'bolsa', 'banco'" << endl;
        break;
    }
}

int Jogo::obtemLimiteUM() const
{
    if (drones)
        return 5;
    else
        return 3;
}

int Jogo::obtemLimiteA() const
{
    if (banco)
        return 5;
    else
        return 3;
}

int Jogo::obtemLimiteC() const
{
    if (banco)
        return 5;
    else
        return 3;
}

int Jogo::obtemFase() const
{
    return nFase;
}

int Jogo::obtemTurnos() const
{
    return nTurnos;
}

int Jogo::obtemAno() const
{
    if (nTurnos < 7)
        return 1;
    else
        return 2;
}

string Jogo::avisoInvalido(string msg)
{
    ostringstream oss;
    if (msg != "desisto")
    {
        if (msg != "comandos")
        {
            oss << "[ERRO] COMANDO INEXISTENTE [ERRO]" << endl;
        }
        if (nFase == 1)
            oss << "Lista: 'conquista', 'lista','lista <nome>','fevento <nome-evento>','modifica <ouro|prod> N', 'toma <terr|tec> <nome>', 'carrega <ficheiro>', 'grava <nome>', 'ativa <nome>', apaga <nome>', 'passa', 'comandos', 'desisto', 'limpa'" << endl;
        else if (nFase == 2)
            oss << "Lista: 'maisouro', 'maisprod', 'lista', 'lista <nome>', 'fevento <nome-evento>', 'modifica <ouro|prod> N', 'toma <terr|tec> <nome>', 'carrega <ficheiro>', 'grava <nome>', 'ativa <nome>', apaga <nome>', 'passa', 'comandos', 'desisto', 'limpa'" << endl;
        else if (nFase == 3)
            oss << "Lista: 'maismilitar', 'adquire <nome>', 'lista', 'lista <nome>', 'fevento <nome-evento>', 'modifica <ouro|prod> N', 'toma <terr|tec> <nome>', 'carrega <ficheiro>', 'grava <nome>', 'ativa <nome>', apaga <nome>', 'passa', 'comandos', 'desisto', 'limpa'" << endl;
    }
    return oss.str();
}

string Jogo::lista() const
{
    ostringstream oss;
    oss << "Ano: " << obtemAno() << "    Turno: " << nTurnos << "    Fator Sorte: " << fatorSorte << endl;
    oss << "Territorios Conquistados: " << endl; //Territorios conquistados
    oss << d->obtemStringImperio(nTurnos);
    oss << "Territorios Por Conquistar: " << endl; //Territorios por conquistar
    oss << d->obtemStringMundo(nTurnos);
    oss << "Ouro: " << endl;
    oss << " -> Valor Atual: " << cofre << "\n -> Capacidade: " << obtemLimiteC() << "\n -> Producao Atual: " << d->obtemOuroGerado(nTurnos) << endl;
    oss << "Produtos: " << endl;
    oss << " -> Valor Atual: " << armazem << "\n -> Capacidade: " << obtemLimiteA() << "\n -> Producao Atual: " << d->obtemProdutoGerado(nTurnos) << endl;
    oss << "Forca Militar: " << endl;
    oss << " -> Valor Atual: " << unidadeMilitar << "\n -> Capacidade: " << obtemLimiteUM() << endl;
    oss << "Tecnologias Existentes:\n"
        << obtemExistentes();
    oss << "Evento:\n  " << ultimoEvento();
    oss << "Pontuacao: " << (d->totalPontos()) << endl;
    return oss.str();
}

string Jogo::lista(string nome) const
{
    ostringstream oss;
    oss << d->obtemTerritorio(nome, nTurnos);
    return oss.str();
}

string Jogo::obtemExistentes() const
{
    ostringstream oss;
    oss << "Drones Militares:\n  Preco: 3 Ouros\n  Resumo: Aumenta o limite de unidades militares\n  " << devolveEstado("drones") << endl;
    oss << "Misseis Teleguiados:\n  Preco: 4 Ouros\n  Resumo: Permite conquistar Ilhas\n  " << devolveEstado("misseis") << endl;
    oss << "Defesas Territoriais:\n  Preco: 4 Ouros\n  Resumo: Acrescenta 1 de resistencia a um territorio invadido\n  " << devolveEstado("defesa") << endl;
    oss << "Bolsa de valores:\n  Preco: 2 Ouros\n  Resumo: Permite a troca entre produtos e ouro\n  " << devolveEstado("bolsa") << endl;
    oss << "Banco Central:\n  Preco: 3 Ouros\n  Resumo: Aumenta o limite do Armazem e do Cofre\n  " << devolveEstado("banco") << endl;
    return oss.str();
}

string Jogo::ultimoEvento() const
{
    ostringstream oss;
    if (ultimo == "recurso")
    {
        oss << "Recurso: Adiciona 1 produto no primeiro ano e 1 ouro no segundo ano" << endl;
    }
    else if (ultimo == "invasao")
    {
        oss << "Invasao: O ultimo território conquistado e invadido" << endl;
    }
    else if (ultimo == "alianca")
    {
        oss << "Alianca: Adiciona 1 unidade militar ao imperio" << endl;
    }
    else
    {
        oss << "Sem Evento" << endl;
    }
    return oss.str();
}

int Jogo::totalTec()
{
    if (contaTec())
    {
        aviso("[AVISO] BONUS CIENTIFICO [AVISO]");
        return 6;
    }
    int aux = 0;
    if (drones)
        ++aux;
    if (misseis)
        ++aux;
    if (defesa)
        ++aux;
    if (bolsa)
        ++aux;
    if (banco)
        ++aux;

    return aux;
}

string Jogo::devolveEstado(string nome) const
{
    ostringstream oss;
    if (nome == "misseis")
    {
        if (misseis)
            oss << "ADQUIRIDA";
        else
            oss << "POR ADQUIRIR";
    }
    else if (nome == "drones")
    {
        if (drones)
            oss << "ADQUIRIDA";
        else
            oss << "POR ADQUIRIR";
    }
    else if (nome == "defesa")
    {
        if (defesa)
            oss << "ADQUIRIDA";
        else
            oss << "POR ADQUIRIR";
    }
    else if (nome == "bolsa")
    {
        if (bolsa)
            oss << "ADQUIRIDA";
        else
            oss << "POR ADQUIRIR";
    }
    else if (nome == "banco")
    {
        if (banco)
            oss << "ADQUIRIDA";
        else
            oss << "POR ADQUIRIR";
    }
    return oss.str();
}

bool Jogo::contaTec()
{
    if (bolsa && misseis && banco && drones && defesa)
        return true;
    else
        return false;
}

void Jogo::carregaC(string nomeF, Memoria &m)
{
    ifstream fich(nomeF);
    string comando;

    if (fich.is_open())
    {
        while (getline(fich, comando))
        {
            cout << comando << endl;
            comandosJ(comando, m);
        }
        fich.close();
    }
    else
    {
        erro("[ERRO] Ficheiro inexistente [ERRO]");
    }
}

string Jogo::obtemNome() const
{
    return nome;
}

Jogo &Jogo::operator=(const Jogo &outro)
{
    if (this == &outro)
        return *this;
    nome = outro.nome;
    nTurnos = outro.nTurnos;
    nFase = outro.nFase;
    fatorSorte = outro.fatorSorte;
    unidadeMilitar = outro.unidadeMilitar;
    armazem = outro.armazem;
    cofre = outro.cofre;
    drones = outro.drones;
    misseis = outro.misseis;
    defesa = outro.defesa;
    bolsa = outro.bolsa;
    banco = outro.banco;
    recolha = outro.recolha;
    compraM = outro.compraM;
    compraT = outro.compraT;
    d = new Mapa(*outro.d);
    return *this;
}

Mapa *Jogo::obtemMapa() const
{
    return d;
}