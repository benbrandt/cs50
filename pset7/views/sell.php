<?php if (isset($cash)): ?>
    <div class="alert alert-success" role="alert">
        Your new balance is <?= trim_zeroes($cash) ?>
    </div>
<?php endif ?>