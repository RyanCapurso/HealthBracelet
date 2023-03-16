<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="./Assets/css/reset.css" rel="stylesheet">
    <link href="./Assets/css/geral.css" rel="stylesheet">
    <link href="./Assets/css/header.css" rel="stylesheet">
    <link href="./Assets/css/footer.css" rel="stylesheet">
    <link href="./Assets/css/register/registros.css" rel="stylesheet">
    <link href="./Assets/css/register/registros_tabela.css" rel="stylesheet">
    <title>Registros</title>
</head>

<body>
    <header class="cabecalho">
        <div class="box">
            <h1 class="title-page"><strong>Health</strong> Bracelet</h1>
            <img id="logotipo" src="./Assets/IMG/hearth.png">
            <nav class="navegation">
                <ul>
                    <li class="navegation-itens"><a href="./index.html">Home</a></li>
                    <li class="navegation-itens">|</li>
                    <li class="navegation-itens"><a href="./registros.php">Registros</a></li>
                    <li class="navegation-itens">|</li>
                    <li class="navegation-itens"><a href="./sobre.html">Quem somos</a></li>
                    <li class="navegation-itens">|</li>
                    <li class="navegation-itens"><a href="./contato.html">Contato</a></li>
                </ul>
            </nav>
            <div class="contato">
                <img id="contato-icon" src="./Assets/IMG/phone.png">
                <p id="telefone">(46) 2134-5489</p>
            </div>
        </div>
    </header>
    <main class="conteudo">
        <div class="container">
            <div class="filtro">
                <form class="teste" action="" method="post">
                    <label class="filtrar" for="pesquisa">Filtrar: </label>
                    <input id="pesquisa" type="text" name="data" placeholder="Mês/Ano">
                    <input class="enviar" type="submit" name="submit" value="Buscar">
                </form>
            </div>
            <div class="registros">
                <?php
                include("conexao.php");

                if ($_SERVER["REQUEST_METHOD"] == "POST") {
                    // echo "<h1> Recebeu a data: " . $_POST["data"] . "</h1>";
                    $dataPesquisa = $_POST['data'];
                    $dataArray = explode("/", $dataPesquisa);
                    $dataPesquisa = $dataArray[1] . "-" . $dataArray[0];
                    //echo "Data pesquisada: " . $dataPesquisa;
                
                    $sql = "SELECT * FROM tbdados WHERE data_hora LIKE '%" . $dataPesquisa . "%' ";
                } else {
                    // echo "<h1> Não recebeu nada, vai mostrar o mês atual</h1>";
                    $dataAtual = date("Y-m");
                    //echo "mês atual: " . $dataAtual;
                    $sql = "SELECT * FROM tbdados WHERE data_hora LIKE '%" . $dataAtual . "%' ";
                }

                $stmt = $PDO->prepare($sql);
                $stmt->execute();

                echo "<table class='tabela'>";

                echo "<tr class='celulas'>
                                    <th>Registro</th>
                                    <th>Data/Hora</th>
                                </tr>";

                while ($linha = $stmt->fetch(PDO::FETCH_OBJ)) {

                    $timestamp = strtotime($linha->data_hora);
                    $dataTabela = date("d/m/Y H:i:s", $timestamp);
                    echo "<tr class='celulas'> ";
                    echo "<td>" . $linha->Esp32 . "</td>";
                    echo "<td>" . $dataTabela . "</td>";
                    echo "</tr>";
                }

                echo "</table>";
                ?>
            </div>
        </div>
    </main>
    <footer class="rodape">
        <div class="rodape-container">
            <div class="social">
                <a href="https://www.facebook.com/" target="_blank"><img class="redes-sociais"
                        src="assets/img/facebook.png"></a>
                <a href="https://www.instagram.com/" target="_blank"><img class="redes-sociais"
                        src="assets/img/instagram.png"></a>
                <a href="https://twitter.com/?lang=pt" target="_blank"><img class="redes-sociais"
                        src="assets/img/twitter.png"></a>
                <a href="https://www.whatsapp.com/?lang=pt_br" target="_blank"><img class="redes-sociais"
                        src="assets/img/whatsapp.png"></a>
                <a href="https://www.youtube.com/watch?v=oNH_E4ClxSE" target="_blank"><img class="redes-sociais"
                        src="assets/img/youtube.png"></a>
            </div>
            <p class="copyright">&copy; Copyright Projeto Integrador - 2021</p>
        </div>
    </footer>
</body>

</html>