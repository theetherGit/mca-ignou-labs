<script lang="ts">
    let pairs: { name: string; value: string }[] = $state([]);

    function parseCookies() {
        pairs = document.cookie
            ? document.cookie
                  .split(";")
                  .map((p) => {
                      const [name, value] = p.split("=").map((s) => s.trim());
                      return { name, value };
                  })
                  .filter((c) => c.name)
            : [];
    }
</script>

<div
    class="p-8 bg-gray-50 min-h-auto text-black rounded-xl mt-5 flex flex-col items-center justify-center gap-4"
>
    <h3 class="text-lg font-semibold text-gray-800">
        All Cookies (Name-Value Pairs)
    </h3>
    <button
        onclick={parseCookies}
        class="px-5 py-2 bg-indigo-600 text-white rounded hover:bg-indigo-700 transition"
        >Parse & Display</button
    >

    <ul
        class="w-full max-w-md bg-white rounded-xl shadow-md divide-y divide-gray-200 overflow-hidden"
    >
        {#if pairs.length === 0}
            <li class="p-4 text-gray-500 text-center">No cookies found</li>
        {:else}
            {#each pairs as c}
                <li class="p-4 flex justify-between">
                    <span class="font-semibold text-gray-700">{c.name}:</span>
                    <span class="text-blue-600 font-medium">{c.value}</span>
                </li>
            {/each}
        {/if}
    </ul>
</div>
