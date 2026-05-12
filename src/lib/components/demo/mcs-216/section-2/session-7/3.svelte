<script lang="ts">
    let idxInput = $state("");
    let animalRes = $state("");
    let finallyMsg = $state("");

    const animals = [
        { id: 0, name: "Lion" },
        { id: 1, name: "Elephant" },
        { id: 2, name: "Tiger" },
    ];

    function lookupAnimal() {
        const idx = parseInt(idxInput);
        try {
            const animal = animals[idx];
            if (!animal)
                throw new TypeError(`Index ${idx} does not contain an animal.`);
            animalRes = `🦁 Animal: ${animal.name}`;
        } catch (err) {
            const error = err instanceof Error ? err : new Error(String(err));
            animalRes = `❌ ${error.message}`;
        } finally {
            finallyMsg = `📝 Checked index: ${idxInput} (Executed via finally)`;
        }
    }
</script>

<div
    class="p-8 bg-gray-50 min-h-auto text-black mt-5 rounded-xl flex flex-col items-center justify-center gap-4"
>
    <h2 class="text-xl font-semibold text-gray-800">Animal Lookup</h2>
    <div class="flex gap-2">
        <input
            bind:value={idxInput}
            type="number"
            placeholder="Enter index (0-2)"
            class="border border-gray-300 px-4 py-2 rounded focus:outline-blue-500"
        />
        <button
            onclick={lookupAnimal}
            class="px-5 py-2 bg-purple-600 text-white rounded hover:bg-purple-700 transition"
            >Find</button
        >
    </div>
    <p class="text-lg font-medium text-gray-700 min-h-6">{animalRes}</p>
    <p class="text-sm text-gray-500 italic">{finallyMsg}</p>
</div>
