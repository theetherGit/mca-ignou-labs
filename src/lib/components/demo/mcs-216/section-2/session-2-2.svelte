<script lang="ts">
    const processors = [
        "Intel i7",
        "Motorola 68000",
        "AMD Athlon",
        "Intel 8088",
        "AMD Ryzen",
        "Intel Pentium MMX",
        "Intel i3",
        "Intel Pentium II",
        "Intel Pentium III",
        "Intel i5",
        "Intel Celeron",
        "PowerPC G3",
        "PowerPC G4",
    ];
</script>

<div
    class="w-full h-svh mt-5 bg-white rounded-2xl shadow-2xl overflow-y-auto scroll-smooth relative"
>
    <header
        class="sticky top-0 z-2 bg-slate-900 text-white p-4 text-center font-bold text-lg shadow-md"
    >
        PC Processors
    </header>

    <ul class="m-0 p-0 list-none">
        {#each processors as processor, index}
            <li
                class="px-6 py-5 border-b border-slate-200 flex items-center gap-4 hover:bg-slate-50 transition-colors duration-200 last:border-b-0"
            >
                <span
                    class="shrink-0 w-10 h-10 bg-linear-to-br from-blue-500 to-violet-600 rounded-xl flex items-center justify-center text-white text-sm font-bold shadow-sm"
                >
                    {index + 1}
                </span>
                <span class="text-slate-800 font-medium text-base">
                    {processor}
                </span>
            </li>
        {/each}
    </ul>
</div>
