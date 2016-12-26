<div>
    <table class="table table-striped text-center">
        <thead>
            <th class="text-center">Transaction</th>
            <th class="text-center">Symbol</th>
            <th class="text-center">Shares</th>
            <th class="text-center">Price</th>
            <th class="text-center">Time</th>
        </thead>
        <tbody>
            <?php foreach ($transactions as $transaction) : ?>
                <tr>
                    <td><?= $transaction["transaction"] ?></td>
                    <td><?= $transaction["symbol"] ?></td>
                    <td><?= $transaction["shares"] ?></td>
                    <td><?= trim_zeroes($transaction["price"]) ?></td>
                    <td><?= $transaction["time"] ?></td>
                </tr>
            <?php endforeach; ?>
        </tbody>
    </table>
</div>
