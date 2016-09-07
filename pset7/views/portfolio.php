<div>
    <h3>Current Balance: $<?= trim_zeroes($cash) ?></h3>
    <table class="table table-striped text-center">
        <thead>
            <th class="text-center">Symbol</th>
            <th class="text-center">Name</th>
            <th class="text-center">Shares</th>
            <th class="text-center">Price</th>
            <th class="text-center">Value</th>
        </thead>
        <tbody>
            <?php foreach ($stocks as $stock) : ?>
                <tr>
                    <td><?= $stock["symbol"] ?></td>
                    <td><?= $stock["name"] ?></td>
                    <td><?= $stock["shares"] ?></td>
                    <td><?= trim_zeroes($stock["price"]) ?></td>
                    <td><?= trim_zeroes($stock["price"] * $stock["shares"]) ?></td>
                </tr>
            <?php endforeach; ?>
        </tbody>
    </table>
</div>
