<script lang="ts">
    const inputvalue = $state({
        1: "1+1",
        2: "1+1*2",
        result1: "2",
        result2: "3",
    });

    function onInputChange(index: 1 | 2) {
        inputvalue[`result${index}`] = eval(inputvalue[index]);
    }
</script>

<div class="grid grid-cols-2 border p-1 w-1/3 mt-3 gap-1">
    <p class="border p-1 px-2 font-bold">Expression</p>
    <p class="border p-1 px-2 font-bold">Result</p>
    <input
        onchange={() => onInputChange(1)}
        class="border p-1 px-2 font-bold"
        bind:value={inputvalue[1]}
        id="expression-1"
    />
    <input
        class="border p-1 px-2 font-bold"
        id="result-1"
        bind:value={inputvalue.result1}
    />
    <input
        onchange={() => onInputChange(2)}
        class="border p-1 px-2 font-bold"
        bind:value={inputvalue[2]}
        id="expression-2"
    />
    <input
        class="border p-1 px-2 font-bold"
        id="result-1"
        bind:value={inputvalue.result2}
    />
</div>
