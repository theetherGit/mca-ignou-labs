<script lang="ts">
    type Year = 1 | 2 | 3 | 4;

    let {
        year,
        navigateTo,
    }: { year: Year; navigateTo: (year: Year | null) => void } = $props();

    const days = ["Mon", "Tue", "Wed", "Thu", "Fri"];
    const getSuffix = (n: number) =>
        n === 1 ? "st" : n === 2 ? "nd" : n === 3 ? "rd" : "th";

    // Year-specific configuration (data + Tailwind header classes)
    const yearConfig: Record<
        Year,
        { header: string; slots: string[][] }
    > = {
        1: {
            header: "bg-blue-600 text-white",
            slots: [
                ["Mathematics", "Physics", "English", "CS", "Physics Lab"],
                [
                    "Chemistry",
                    "Mathematics",
                    "Physics",
                    "Workshop",
                    "Chemistry Lab",
                ],
                ["English", "Chemistry", "Workshop", "Mathematics", "CS"],
            ],
        },
        2: {
            header: "bg-green-600 text-white",
            slots: [
                ["OS", "DBMS", "DSA", "COA", "Lab"],
                ["Math III", "Algorithms", "Networks", "Web Tech", "Lab"],
                ["Elective I", "Compiler", "AI Basics", "Seminar", "Project"],
            ],
        },
        3: {
            header: "bg-purple-600 text-white",
            slots: [
                ["AI", "Cloud", "Cyber Sec", "ML", "Lab"],
                ["Distributed Sys", "IoT", "Research", "Elective II", "Lab"],
                [
                    "Major Project",
                    "Guest Lec",
                    "Industry Visit",
                    "Review",
                    "Documentation",
                ],
            ],
        },
        4: {
            header: "bg-yellow-400 text-black",
            slots: [
                [
                    "Internship",
                    "Placement Prep",
                    "Elective III",
                    "Viva",
                    "Project I",
                ],
                [
                    "Capstone",
                    "Tech Writing",
                    "Mentorship",
                    "Mock Interview",
                    "Project II",
                ],
                [
                    "Final Review",
                    "Report Sub.",
                    "Presentation",
                    "Clearance",
                    "Farewell",
                ],
            ],
        },
    };

    let config = $derived(yearConfig[year] ?? yearConfig[1]);
</script>

<section class="p-6 max-w-5xl mx-auto">
    <header class="text-center mb-6">
        <h1 class="text-2xl font-bold text-gray-900">
            {year}{getSuffix(year)} Year B.Tech Timetable
        </h1>
    </header>

    <div class="overflow-x-auto bg-white rounded-xl shadow-md">
        <table class="w-full border-collapse">
            <thead>
                <!-- ✅ Year-specific header styling -->
                <tr class={config.header}>
                    <th class="p-3 border border-gray-300/50">Time</th>
                    <!-- ✅ Common: Bold + First letter uppercase -->
                    {#each days as day}
                        <th
                            class="p-3 border border-gray-300/50 font-bold capitalize"
                            >{day}</th
                        >
                    {/each}
                </tr>
            </thead>
            <tbody>
                {#each config.slots as subjects, index}
                    <tr class="hover:bg-gray-50 transition">
                        <td
                            class="p-3 border border-gray-200 text-center font-medium bg-gray-50"
                        >
                            {9 + index}:00 - {10 + index}:00
                        </td>
                        {#each subjects as subject}
                            <td class="p-3 border border-gray-200 text-center"
                                >{subject}</td
                            >
                        {/each}
                    </tr>

                    <!-- ✅ Common: Lunch slightly bigger font -->
                    {#if index === 0}
                        <tr>
                            <td
                                class="p-4 border border-gray-200 text-center text-lg font-bold bg-amber-50 text-amber-800"
                                colspan="6"
                            >
                                LUNCH BREAK
                            </td>
                        </tr>
                    {/if}
                {/each}
            </tbody>
        </table>
    </div>

    <div class="text-center mt-6">
        <button
            onclick={() => navigateTo(null)}
            class="px-5 py-2 bg-gray-200 hover:bg-gray-300 rounded-lg font-medium transition"
        >
            ← Back to Home
        </button>
    </div>
</section>
