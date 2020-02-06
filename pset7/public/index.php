<?php

    // configuration
    require("../includes/config.php"); 
        
    // lookup portfolio and store in Session
    $_SESSION["portfolio"] = get_user_portfolio();
    
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio"]);

?>
