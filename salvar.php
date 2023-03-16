<?php

    include("conexao.php");

    $Esp32 = $_GET['Esp32'];

    $sql = "INSERT INTO tbdados (Esp32) VALUES (:Esp32)";

    $stmt = $PDO->prepare($sql);

    $stmt->bindParam(":Esp32", $Esp32);

    if($stmt->execute()) {
        echo "salvo_com_sucesso";
    } else {
        echo "erro_ao_salvar";
    }

?>