<?php

// configuration
require("../includes/config.php"); 

// render header
require("../templates/header.php");

require("../templates/nav_links.php");
?>

<table class="table table-striped">

     <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>

    <tbody>

    <?php 
    $rows = get_user_history();   
     
    // user`, `transaction`, `time`, `symbol`, `shares`, `price`  
    foreach ($rows as $row)
    {
        
        // set buy/sell
        if($row["transaction"] == 0)
        {
            $transaction = 'SELL';
        }
        else
        {
            $transaction = 'BUY';
        }
    
        print("\n    <tr class='table-striped'>\n");
        print("\t <td>{$transaction}</td>\n");
        print("\t <td>{$row["time"]}</td>\n");
        print("\t <td>{$row["symbol"]}</td>\n");
        print("\t <td>{$row["shares"]}</td>\n");
        print("\t <td>\${$row["price"]}</td>\n");
        print("    </tr> \n");
       
    }
    
    ?>

    </tbody>

</table>
            
           

<div>
    <a href="logout.php">Log Out</a>
</div>
<?php
// render footer
            require("../templates/footer.php");
?>

