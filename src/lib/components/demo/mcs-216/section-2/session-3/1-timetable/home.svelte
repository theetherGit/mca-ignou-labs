<script lang="ts">
    let { navigateTo } = $props();

    const years = [1, 2, 3, 4];
    const getSuffix = (n: number) =>
        n === 1 ? "st" : n === 2 ? "nd" : n === 3 ? "rd" : "th";
</script>

<section class="p-6 max-w-4xl mx-auto">
    <header class="text-center mb-10">
        <h1 class="text-3xl font-bold tracking-tight text-gray-900">
            B.Tech Even Semester Timetables
        </h1>
        <p class="text-gray-500 mt-2">Select a year to view the schedule</p>
    </header>

    <nav class="flex flex-wrap justify-center gap-4">
        {#each years as year}
            <button
                onclick={() => navigateTo(year)}
                class="px-6 py-3 bg-white border-2 border-gray-200 rounded-xl shadow-sm hover:border-blue-500 hover:text-blue-600 transition-all font-semibold"
            >
                {year}{getSuffix(year)} Year Timetable
            </button>
        {/each}
    </nav>
</section>
